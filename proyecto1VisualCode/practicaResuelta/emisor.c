#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <signal.h>
#include "libPractica.h"

#define RUTA_PIPE "/tmp/tub.pipe"
#define TAM_MAX 100

bool finalPrograma = false;

int main(int argc, char const *argv[]){
  int pipe = prepararPipe(RUTA_PIPE);
  signal(SIGUSR1,tratarSIGUSR1);
  char buffer[TAM_MAX];
  pid_t pid = getpid();
  if (write(pipe,&pid,sizeof(pid_t)) == -1){
      perror("Error en el write del pid");
      exit(-2);
  }
  while(!finalPrograma){
    fgets(buffer,TAM_MAX,stdin);
    //fscanf(stdin,"%[^\n]%*c");
    if(write(pipe,buffer,(strlen(buffer)+1)*sizeof(char)) == -1){
      perror("Error en el write");
      exit(-2);
    }
  }
  close(pipe);
  system("rm "RUTA_PIPE);
  return 0;
}

void tratarSIGUSR1(int senyal){
  finalPrograma = true;
  printf("El receptor me ha enviado una señal de salida.");
  fflush(stdout);
  //Al cerrar la entrada estándar, el fgets sale sin leer nada y conseguimos
  //que se vuelva a evaluar en el bucle.
  fclose(stdin);
}

