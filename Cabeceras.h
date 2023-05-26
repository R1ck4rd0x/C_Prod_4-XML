#pragma once
#include "Definiciones.h"
#include <stdbool.h>
#ifndef Cabeceras_h
#define Cabeceras_h

// DECLARACIÓN DE FUNCIONES

//int read_ip_address(char* str, IP_ADDRESS* ip);
int read_Adaptors();
int read_Adaptador_Info(int adapter_index, ADAPTADOR_INFO* adaptador_info);
void crearArchivoXML(int adapter_index, ADAPTADOR_INFO* adaptador_info);
int tracert(ADAPTADOR_INFO* adaptador_info);
char* extractFirstDNS(ADAPTADOR_INFO* adaptador_info);


#endif