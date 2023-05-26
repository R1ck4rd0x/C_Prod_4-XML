/* Producto 3. Automatización básica de la administración de un sistema operativo
*  Ricardo Mesa
*/
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

// Incluimos las librerias necesarias 
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <windns.h>
#include "Cabeceras.h"
#include "Definiciones.h"

// Enlazamos las librerias que lo necesitan 
#pragma comment(lib, "iphlpapi.lib") 
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Dnsapi.lib")

int main() {
    
    // Variable con la estructura del adaptador definida en Definiciones.h
    ADAPTADOR_INFO adaptador_info;

    // Presentación
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
    printf("\n----------------------- INFORME DE ADAPTADOR A XML v3.4 (c)2023 by CodeCluster for UOC --------------------------------");
    printf("\n-----------------------------------------------------------------------------------------------------------------------\n");

   
    //------------------ Paso 1: Mostrar los adaptadores del equipo por pantalla, de los que se le pide al usuario que elija uno.

    // Llamamos a la función que leerá los adaptadores Y nos devolverá el adaptador elegido por el usuario
    printf("\n A continuación se examinarán todos los adaptadores de red de su equipo. ");
    system("pause");
    int adapter_index = read_Adaptors();

    // Llamamos a la función que extrae los datos necesarios del adaptador elegido y los mostramos al usuario
    if (read_Adaptador_Info(adapter_index, &adaptador_info) == 0) {
        printf("\nAdaptador {IPv4, IPv6}:    %s\n", adaptador_info.adaptador_IP);
        printf("Subnet Mask {IP, Prefijo}: %s\n", adaptador_info.subnet_Mask);
        printf("Puerta de enlace predeterminada {IP}:    %s\n", adaptador_info.gateway);
        printf("DNS configurados {primario, secundario}: %s\n", adaptador_info.DNS_primario);
    }
    else {
        printf("No se pudo obtener la información del adaptador.\n");
    }

    // Llamamos a la función que nos extrae el DNS primario de los guardados en la estructura
    char* target_ip = extractFirstDNS(&adaptador_info);

    printf("IP del DNS primario a examinar: %s\"... Testeando la conexión y creando el informe en un archivo XML, espere...\n", target_ip);

    
    // Lamamos a la función que calcula la media en ms, el nº de saltos y la IP de cada salto
    tracert(&adaptador_info, target_ip);

    // Llamamos a la función que crea y escribe el archivo XML
    crearArchivoXML(adapter_index, &adaptador_info);

    free(target_ip);


    return 0;
}

    