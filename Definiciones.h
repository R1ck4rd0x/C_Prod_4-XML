#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

#ifndef Definiciones_H
#define Definiciones_H
#define MAX_HOPS 30
#define MAX_LINE_LENGTH 256
#define MAX_LINE2_LENGTH 46
#define INET_ADDRSTRLEN 16


// Estructura para la información del adaptador
typedef struct {
    char description[MAX_LINE2_LENGTH];
    char adaptador_IP[MAX_LINE2_LENGTH];
    char subnet_Mask[MAX_LINE2_LENGTH];
    char DNS_primario[MAX_LINE2_LENGTH];
    char gateway[INET_ADDRSTRLEN];
    float media_tiempos;
    int num_hops;
    char ip_hop[MAX_LINE_LENGTH];
} ADAPTADOR_INFO;



// Estructura para los servidores DNS de un adaptador
typedef struct {
    char ip[16];
    int hops;
    int response_time;
} DNS_ADAPT;


#endif // Definiciones_H