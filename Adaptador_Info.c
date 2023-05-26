#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include "Cabeceras.h"
#include "Definiciones.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")



int read_Adaptador_Info(int adapter_index, ADAPTADOR_INFO* adaptador_info) {
 
    // Variables para almacenar la información del adaptador de red
    char ip_address[256];
    char subnet_mask[256];
    char default_gateway[256];
    char description[256];
    char primary_dns[256] = "";  // Variable para almacenar el DNS primario

    // Construir el comando wmic para obtener la información del adaptador de red
    char command[256];
    sprintf_s(command, sizeof(command), "wmic nicconfig where 'index=%d' get Description,IPAddress,IPSubnet,DefaultIPGateway, DNSServerSearchOrder /value", adapter_index);

    // Abrir el proceso para leer la salida de wmic
    FILE* fp = _popen(command, "r");
    if (fp == NULL) {
        printf("Error al abrir el proceso.\n");
        return -1;  // o cualquier otro código de error que desees utilizar
    }

   
    // Bucle para leer la salida línea por línea
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Buscar la información relevante en cada línea y almacenarla en las variables correspondientes
         
        // Buscar la descripci´´on
        if (strstr(line, "Description") != NULL) {
            char* value = strchr(line, '=');
            if (value != NULL) {
                strncpy_s(description, sizeof(description), value + 1, _TRUNCATE);
            }
        }
               
        // Ejemplo: buscar la dirección IP
        if (strstr(line, "IPAddress") != NULL) {
            char* value = strchr(line, '=');
            if (value != NULL) {
                strncpy_s(ip_address, sizeof(ip_address), value + 1, _TRUNCATE);
            }
        }
        // Ejemplo: buscar la máscara de subred
        else if (strstr(line, "IPSubnet") != NULL) {
            char* value = strchr(line, '=');
            if (value != NULL) {
                strncpy_s(subnet_mask, sizeof(subnet_mask), value + 1, _TRUNCATE);
            }
        }
        // Ejemplo: buscar la puerta de enlace predeterminada
        else if (strstr(line, "DefaultIPGateway") != NULL) {
            char* value = strchr(line, '=');
            if (value != NULL) {
                strncpy_s(default_gateway, sizeof(default_gateway), value + 1, _TRUNCATE);
            }
        }
        // Ejemplo: buscar el DNS primario
        else if (strstr(line, "DNSServerSearchOrder") != NULL) {
            char* value = strchr(line, '=');
            if (value != NULL) {
                if (strlen(primary_dns) == 0) {
                    // strncpy_s(DNS_primario, sizeof(DNS_primario), value + 1, _TRUNCATE);
                    strncpy_s(primary_dns, sizeof(primary_dns), value + 1, _TRUNCATE);
                }
            }

        }
    }

    // Cerrar el proceso
    _pclose(fp);

    // Guardar la información del adaptador en la estructura ADAPTADOR_INFO
    strncpy_s(adaptador_info->description, sizeof(adaptador_info->description), description, _TRUNCATE);
    strncpy_s(adaptador_info->adaptador_IP, sizeof(adaptador_info->adaptador_IP), ip_address, _TRUNCATE);
    strncpy_s(adaptador_info->subnet_Mask, sizeof(adaptador_info->subnet_Mask), subnet_mask, _TRUNCATE);
    strncpy_s(adaptador_info->gateway, sizeof(adaptador_info->gateway), default_gateway, _TRUNCATE);
    strncpy_s(adaptador_info->DNS_primario, sizeof(adaptador_info->DNS_primario), primary_dns, _TRUNCATE);

    return 0;
}
// Pequeña función que tiene que ver con la anterior, si se extraen 2 DNS, esta elegirá solo el primario
char* extractFirstDNS(ADAPTADOR_INFO* adaptador_info) {
    char* dns = _strdup(adaptador_info->DNS_primario);
    char* token = strtok(dns, ",");
    if (token != NULL) {
        // Eliminar las comillas alrededor del DNS
        memmove(token, token + 1, strlen(token));
        token[strlen(token) - 1] = '\0';
    }
    return token;
}

