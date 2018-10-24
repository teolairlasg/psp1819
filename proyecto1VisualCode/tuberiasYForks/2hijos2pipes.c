#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
     //Creo el array que albergará las direcciones para 
     //la comunicación Padre --> Hijo
    int pPadreHijo[2];
     //Creo el array que albergará las direcciones para 
     //la comunicación Hijo --> Padre
    int pHijoPadre[2];

    //Inicializo los PIPES
    pipe(pPadreHijo);
    pipe(pHijoPadre);
    
    //Creo una variable de pid y bifurco mi programa.
    pid_t pid;
    pid = fork();

    if (pid == 0){ //Código Hijo. Espera a que el padre le envíe algo.
        //cierro la escritura del pipe por el que recibo
        close(pPadreHijo[1]); 
        //cierro la lectura del pipe por el que envío
        close(pHijoPadre[0]); 
        int recibido;
        read(pPadreHijo[0],&recibido,sizeof(int));
        printf("Hijo: Leído %d del pipe.\n",recibido);
        int mensaje = 3432;
        write(pHijoPadre[1],&mensaje,sizeof(int));
    }else{ //Código Padre. Inicia la comunicación
        //cierro la escritura del pipe por el que recibo
        close(pPadreHijo[0]); 
        //cierro la lectura del pipe por el que envío
        close(pHijoPadre[1]);
        int mensaje = 123445;
        write(pPadreHijo[1],&mensaje,sizeof(int));
        int recibido;
        read(pHijoPadre[0],&recibido,sizeof(int));
        printf("Padre: Leído %d del pipe.\n",recibido);
        wait(NULL);
    }
    //Esto lo ejecutan los dos.
    return 0;
}