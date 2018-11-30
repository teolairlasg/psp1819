#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#define LOG "temblores.log"

void tratarSenyal(int);
void tratarSigInt(int);
void obtenerFechaHora(char*);

bool final=false;

int main(int argc, char const *argv[])
{
    signal(SIGUSR1,tratarSenyal);
    signal(SIGUSR2,tratarSenyal);
    signal(SIGINT,tratarSigInt);

    while(!final){
        pause();
    }
    return 0;
}

void tratarSenyal(int codSenyal){
    char fechaHora[24];
    obtenerFechaHora(fechaHora);
    FILE* registro=fopen(LOG,"a");
    switch (codSenyal){
        case SIGUSR1:
            fprintf(registro,"*%s Temblor leve detectado\n",fechaHora);        
        break;
        case SIGUSR2:
            printf("\a");
            fprintf(registro,"**%s Temblor FUERTE detectado\n",fechaHora);
            fprintf(stderr,"TEMBLOR FUERTE\n");
        break;
    }
    fclose(registro);
}

void tratarSigInt(int codSenyal){
    char orden[100];
    char fechaHora[24];
    obtenerFechaHora(fechaHora);
    sprintf(orden,"echo '***%s Error en el Sismógrafo' >> "LOG,fechaHora);
    system(orden);
    final=true;
}

void obtenerFechaHora(char* cadena){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(cadena ,"%d-%.2d-%.2d (%.2d:%.2d:%.2d) -", tm.tm_year + 1900, tm.tm_mon + 1,  tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}