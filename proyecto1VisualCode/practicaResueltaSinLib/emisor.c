#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#define RUTA_PIPE "/tmp/tub.pipe"
#define TAM_MAX 100
//Con esta variable booleana controlo el final de programa.
//Es global porque la actualizaré a la recepción de una señal
//y a la función de la señal no puedo pasarle parámetros
bool finalPrograma = false;

//Declaro las funciones.
void tratarSIGUSR1(int);
int prepararPipe(const char*);

int main(int argc, char const *argv[]){
  //Asocio la señal a la función que la tratará
  signal(SIGUSR1,tratarSIGUSR1);
  //Obtengo el pipe (la función me lo devuelve abierto y listo)
  int pipe = prepararPipe(RUTA_PIPE);
  //Declaro el buffer donde guardaré lo que lea de teclado
  //Será también lo que envíe a través del pipe
  char buffer[TAM_MAX];
  //Obtengo mi pid. Será lo primero que envíe al receptor
  //Lo utilizará para enviarme las señales (lo necesita)
  pid_t pid = getpid();
  //Envío el pid
  if (write(pipe,&pid,sizeof(pid_t)) == -1){
      perror("Error en el write del pid");
      exit(-2);
  }
  //Bucle principal, leer de teclado y enviar mientras la variable
  //booleana finalPrograma se mantenga a falso.
  while(!finalPrograma){
    //Me bloqueo esperando el mensaje por teclado.
    fgets(buffer,TAM_MAX,stdin);
    //fscanf(stdin,"%[^\n]%*c"); //también se puede hacer así (cualquier carácter que no sea \n y descartas el resto de caracteres)
    
    //Envío la lectura (almacenada en buffer) por el pipe.
    //No necesito el & porque el nombre de un vector es su posición de memoria inicial
    //Envío un caracter más para incluir el \0 (strlen me devuelve el número de caracteres de un string sin incluir el \0)
    if(write(pipe,buffer,(strlen(buffer)+1)*sizeof(char)) == -1){
      perror("Error en el write");
      exit(-2);
    }
  }
  fprintf(stdout,"Recogiendo la casa...");
  close(pipe); //Cierro el pipe
  system("rm "RUTA_PIPE); //Borro el fichero que he usado de pipe
  fprintf(stdout,"Hecho\n");
  return 0;
}


//Función que trata la señal SIGUSR1
void tratarSIGUSR1(int senyal){
  //Si recibo esta señal, es para acabar el programa.
  finalPrograma = true;
  printf("El receptor me ha enviado una señal de salida.");
  fflush(stdout);
  //Al cerrar la entrada estándar, el fgets sale sin leer nada y conseguimos
  //que se vuelva a evaluar en el bucle.
  fclose(stdin);
}


//Esta función creará un archivo de tipo FIFO. (como si hicieramos el mknod)
//luego lo abrirá en modo escritura
int prepararPipe(const char* rutaPipe){
  fprintf(stdout,"Creando el pipe...");
  //man mkfifo para más información :-)
  if ( mkfifo(rutaPipe,0666) == -1){
    perror("Error creando el fichero de PIPE");
    exit(-1);
  }
  printf("Hecho!\n");
  printf("Abriendo el pipe. Esperando a que el receptor lo abra en modo lectura...");
  fflush(stdout); //Fuerzo a que se escriba inmediatamente el mensaje anterior.
  int descriptor = open(rutaPipe,O_WRONLY);
  if ( descriptor == -1 ){
    perror("Error abriendo el PIPE");
    exit(-2);
  }
  printf("Hecho!\n");
  return descriptor;
}