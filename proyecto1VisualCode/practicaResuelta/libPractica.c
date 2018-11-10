#include "libPractica.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include <time.h>

int abrirPipe(const char* rutaPipe){
  printf("Abriendo el pipe...");
  int descriptor = open(rutaPipe,O_RDONLY);
  if ( descriptor == -1 ){
    perror("Error abriendo el PIPE");
    exit(-1);
  }
  printf("Hecho!\n");
  return descriptor;
}

void rellenarFechaYHora(char *cadena){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(cadena ,"%2d/%2d/%4d (%d:%d:%d) -", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

int prepararPipe(const char* rutaPipe){
  fprintf(stderr,"Creando el pipe...");
  if ( mkfifo(rutaPipe,0666) == -1){
    perror("Error creando el fichero de PIPE");
    exit(-1);
  }
  printf("Hecho!\n");
  printf("Abriendo el pipe...");
  int descriptor = open(rutaPipe,O_WRONLY);
  if ( descriptor == -1 ){
    perror("Error abriendo el PIPE");
    exit(-2);
  }
  printf("Hecho!\n");
  return descriptor;
}