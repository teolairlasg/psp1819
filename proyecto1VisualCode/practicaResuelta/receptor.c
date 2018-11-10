#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include "libPractica.h"

bool finalPrograma = false;
pid_t pid;

#define RUTA_PIPE "/tmp/tub.pipe"
#define RUTA_LOG "./log.txt"
#define TAM_MAX 100

void tratarCtrlC(int);
void tratar2oCtrlC(int);

int main(int argc, char const *argv[])
{
  int pipe = abrirPipe(RUTA_PIPE);
  read(pipe,&pid,sizeof(pid_t));
  printf("El PID del emisor es: %d\n", pid);
  char* buffer;
  signal(SIGINT,tratarCtrlC);
  buffer = (char*) malloc(TAM_MAX);
  FILE* registro = fopen(RUTA_LOG,"a"); 
  int bytesLeidos;
  while(!finalPrograma){
    bytesLeidos = read(pipe,buffer,TAM_MAX);
    if( bytesLeidos == -1){
      perror("Error en el read");
      exit(-2);
    }
    if( bytesLeidos != 0){
      char fechaHora[24];
      rellenarFechaYHora(fechaHora);
      fprintf(registro,"%s %s\n",fechaHora,buffer);
      fprintf(stderr,"%s %s\n",fechaHora,buffer);
    }
  }
  fclose(registro);
  close(pipe);
  return 0;
}

void tratarCtrlC(int senyal){
  kill(pid,SIGUSR1);
  printf("Vuelva a pulsar Ctrl-C para salir");
  fflush(stdout);
  signal(SIGINT,tratar2oCtrlC);
}

void tratar2oCtrlC(int senyal){
  printf("Saliendo...\n");
  fflush(stdout);
  finalPrograma = true;
}

