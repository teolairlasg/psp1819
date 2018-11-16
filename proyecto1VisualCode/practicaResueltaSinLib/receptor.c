#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

//Estas variables son globales porque las voy a utilizar dentro de
//Las funciones de tratamiento de señales, y este tipo de función
//no admite más parámetro que el entero que les llega (el código de señal)
//Así que no puedo pasar las variables por parámetro
bool finalPrograma = false;
pid_t pid;

#define RUTA_PIPE "/tmp/tub.pipe"
#define RUTA_LOG "./log.txt"
#define TAM_MAX 100

//Declaro las funciones.
void tratarCtrlC(int);  //Las funciones que tratan señales son obligatoriamente así:
void tratar2oCtrlC(int);//devuelven void y reciben un parámetro entero (el código de la señal)
int abrirPipe(const char*);
void obtenerFechaHora(char*);
void imprimirYRegistrar(char*,FILE*);

int main(int argc, char const *argv[])
{
  //Asocio el primer Ctrl-C a la función.
  signal(SIGINT,tratarCtrlC);
  
  //Abro el pipe. La función coje el fichero creado por el emisor y lo abre en modo lectura
  int pipe = abrirPipe(RUTA_PIPE);
  //Leo del pipe el pid del emisor. Lo necesito para enviarle la señal SIGUSR1 mediante kill
  read(pipe,&pid,sizeof(pid_t));
  //Informo del pid el emisor
  printf("El PID del emisor es: %d\n", pid);

  //Aquí me ha apetecido utilizar memoria dinámica
  //No tiene sentido porque TAM_MAX es estático, pero así lo recordáis.
  //char buffer[TAM_MAX];  //Se podía hacer así.
  char* buffer;
  buffer = (char*) malloc(TAM_MAX);
  
  //Abro el fichero en modo añadir. El log será incremental.
  FILE* registro = fopen(RUTA_LOG,"a"); 

  //Bucle principal del programa. Lee del pipe y lo registra en el log
  char fechaHora[24]; //Aquí guardaré la cadena fecha hora con el formato elegido.
  int bytesLeidos;    //Aquí meteré el retorno del read.
  while(!finalPrograma){
    bytesLeidos = read(pipe,buffer,TAM_MAX);
    if( bytesLeidos == -1){
      perror("Error en el read");
      exit(-2);
    }
    //El siguiente if lo hago, porque si me cierran el otro extremo del pipe
    //el read me retorna con un 0 indefinidamente
    if( bytesLeidos != 0){
      imprimirYRegistrar(buffer, registro);
    }
    if( bytesLeidos == 0 ){
      buffer="El emisor ha cerrado la comunicación";
    }
  }
  fclose(registro);
  close(pipe);
  free(buffer); //Libero la memoria reservada por malloc
  return 0;
}

void imprimirYRegistrar(char* buffer, FILE* registro){
      char fechaHora[24];
      obtenerFechaHora(fechaHora);
      fprintf(registro,"%s %s\n",fechaHora,buffer);
      fprintf(stderr,"%s %s\n",fechaHora,buffer);
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

int abrirPipe(const char* rutaPipe){
  printf("Abriendo el pipe...");
  int descriptor = open(rutaPipe,O_RDONLY);
  if ( descriptor == -1 ){
    perror("Error abriendo el PIPE. ¿Ha lanzado el emisor? Él es el encargado de crear el PIPE.");
    exit(-1);
  }
  printf("Hecho!\n");
  return descriptor;
}

void obtenerFechaHora(char* cadena){
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(cadena ,"%2d/%2d/%4d (%d:%d:%d) -", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
}