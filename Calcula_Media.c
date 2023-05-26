#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <iphlpapi.h>
#include "Cabeceras.h"
#include "Definiciones.h"

// Enlazamos las librerias que lo necesitan 
#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

// Función que calcula los ms, los saltos y si completa la traza o no
int tracert(ADAPTADOR_INFO* adaptador_info, char* target_ip) {
    char command[MAX_LINE_LENGTH];
    char line[MAX_LINE_LENGTH];
    int response_times[MAX_HOPS];
    char ip_hop[MAX_LINE_LENGTH];
    int hop = 0;
    int total_time = 0;



    // Construimos nuestro comando tracert con los la IP que corresponda
    sprintf_s(command, MAX_LINE_LENGTH, "tracert -d -h %d %s", MAX_HOPS, target_ip);

    // Abrimos la tubería para ejecutar el comando construido
    FILE* pipe = _popen(command, "r");
    if (!pipe) {
        printf("Error: No se pudo abrir el comando 'tracert'\n");
        return -1;
    }
   
    ip_hop[0] = '\0';  // Inicializar el buffer ip_hop como una cadena vacía

    // Leemos la salida línea por línea
    while (fgets(line, MAX_LINE_LENGTH, pipe)) {


        // Buscamos el siguiente salto si el puntero de la linea encuentra " " quiere decir que recibimos 
       // respueta y posiciona el puntero despues del espacio que donde se encuentra el número de salto, lo extraemos con "atoi"
        char* ptr_hop = strstr(line, " ");
        if (ptr_hop != NULL && strstr(line, "Traza completa.") == NULL) {
            hop = atoi(ptr_hop);
        }

        if (hop > 0 && hop <= MAX_HOPS) {
            // Buscamos el tiempo de respuesta para el hop actual
            char* ptr = strstr(line, "ms");
            if (ptr != NULL) {
                ptr = ptr - 4;
                int time = atoi(ptr);
                response_times[hop - 1] = time;
                total_time += time;

                // Al haber havido ms se debe haber obtenido la IP del salto
                // Buscar la IP del salto actual
                char ip[MAX_LINE_LENGTH];
                if (sscanf(line, "%*s %*s %*s %*s %*s %*s %*s %s", ip) == 1) {
                    strcat(ip_hop, ip);  // Agregar la IP al string ip_hop
                    strcat(ip_hop, ", ");  // Agregar una coma para separar las IPs
                }

            }
            else if (strstr(line, "Tiempo de espera agotado") != NULL) {
                response_times[hop - 1] = 3000;
                total_time += 3000;
            }
        }

        // Si hemos llegado al final del archivo, salimos del bucle
        if (feof(pipe)) {
            break;
        }

    }
    adaptador_info->media_tiempos = total_time / hop;
    adaptador_info->num_hops = hop;
    strcpy(adaptador_info->ip_hop, ip_hop);

    return 0;

}