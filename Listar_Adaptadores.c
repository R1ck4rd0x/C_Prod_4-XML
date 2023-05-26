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
#pragma comment(lib, "Ws2_32.lib")

#include <stdio.h>
#include <stdlib.h>

int read_Adaptors() {
    char line[256];
    int index;
    char description[256];
    int adapter_indexL = -1;

    // Creamos un comando de consola llamado wmic el cual nos lista los adaptadores 
    // mucho más facilmente que el que usé en el producto anterior.
    FILE* fp = _popen("wmic nicconfig get Index,Description", "r");
    if (fp == NULL) {
        printf("\nError al abrir el proceso.\n");
        return -1;
    }

    // Leer y mostrar la salida del comando wmic
    printf("\nLista de adaptadores de red:\n");
    printf("------------------------------------------------\n");
   
    // Leer y mostrar cada línea de la salida del comando wmic
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
      
    }

    // Cerrar el proceso
    _pclose(fp);

    // Preguntar al usuario por el adaptador que desea modificar
    printf("\nIntroduce el índice del adaptador de red del cual quieres un informa en XML: ");
    scanf("%d", &adapter_indexL);

    return adapter_indexL;
}

