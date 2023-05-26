#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <libxml/parser.h>
//#include <libxml/tree.h>
#include "Cabeceras.h"
#include "Definiciones.h"

void crearArchivoXML(int adapter_index, ADAPTADOR_INFO* adaptador_info) {
    char filename[256];
    FILE* fp;

    // Genera el nombre del archivo XML


    //snprintf(filename, sizeof(filename), "%s.xml", adaptador_info->description);
    snprintf(filename, sizeof(filename), "Adaptador%d.xml", adapter_index);

    // Abre el archivo XML en modo escritura
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("No se pudo crear el archivo XML.\n");
        return;
    }

    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(fp, "<adaptador>\n");
    fprintf(fp, "    <adaptador_IP>\"%s\"</adaptador_IP>\n", adaptador_info->adaptador_IP);
    fprintf(fp, "    <Descripcion>%s</Descripcion>\n", adaptador_info->description);
    fprintf(fp, "    <subnet_Mask>\"%s\"</subnet_Mask>\n", adaptador_info->subnet_Mask);
    fprintf(fp, "    <gateway>\"%s\"</gateway>\n", adaptador_info->gateway);
    fprintf(fp, "    <servidores_DNS>\"%s\"</servidores_DNS>\n", adaptador_info->DNS_primario);
    fprintf(fp, "    <DNS_primario>\n");
    fprintf(fp, "        <Tiempo_medio_en_ms>%.6f</Tiempo_medio_en_ms>\n", adaptador_info->media_tiempos);
    fprintf(fp, "        <numero_de_saltos_del_DNS_primario>%d</numero_de_saltos_del_DNS_primario>\n", adaptador_info->num_hops);
    fprintf(fp, "        <IPs_de_cada_salto>\" %s\"</ IPs_de_cada_salto>\n", adaptador_info->ip_hop);
    fprintf(fp, "    </DNS_primario>\n");
    fprintf(fp, "</adaptador>\n");

    // Cierra el archivo
    fclose(fp);
    printf("\n -----------------------------------------------------------------------------------------------------------------\n");
    printf("------------------------> El archivo XML se ha creado correctamente: [%s] <---------------------------\n", filename);
    printf("------------------------------------------------------------------------------------------------------------------\n");
    printf("\n --------------------------------> TRABAJO REALIZADO!! ^^  HASTA LUEGUITO !!! <-----------------------------------\n");

}
