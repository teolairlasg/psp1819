#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

/** 
 * Set a file descriptor to blocking or non-blocking mode.
 *
 * @param fd The file descriptor
 * @param blocking 0:non-blocking mode, 1:blocking mode
 *
 * @return 1:success, 0:failure.
 **/
int fd_set_blocking(int fd, int blocking) {
    /* Save the current flags */
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
        return 0;

    if (blocking)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;
    return fcntl(fd, F_SETFL, flags) != -1;
}


int main(int argc, char const *argv[])
{
    int tub[2];

    if (pipe(tub) == -1){
        exit(-1);
    }
    int entrada = tub[1];
    int salida = tub[0];
    
    if (fd_set_blocking(entrada, 1) == 0 ){
       fprintf(stderr, "H1: algo ha ido mal estableciendo la entrada a bloqueante\n");
    }
    if (fd_set_blocking(salida, 1) == 0 ){
       fprintf(stderr, "H1: algo ha ido mal estableciendo la entrada a bloqueante\n");
    }

    pid_t pidH1, pidH2;
    pidH1 = fork();

    if (pidH1 == -1){
        exit(-2);
    }
    if (pidH1 == 0){ //Código del hijo 1
        close(salida);
        int msj = 123;
        printf("H1: Enviando entero %d por el pipe...\n",msj);
        fflush(stdout);
        
        write(entrada,&msj,sizeof(int));
        printf("H1: Enviado entero!\n");
    }else{ //Código del padre
        pidH2 = fork();
        if (pidH2 == -1){
            exit(-3);
        }
        if(pidH2 == 0){ //Código del hijo2
            close(entrada);
            int msj_recibido = 0;
            printf("H2: Recibiendo entero por el pipe...\n");
            fflush(stdout);
            sleep(5);
            read(salida,&msj_recibido,sizeof(int));
            printf("H2: Recibido!. He leído %d del pipe\n",msj_recibido);
        }else{ //Código del padre
            printf("Padre: Esperando a un hijo...\n");
            wait(NULL);
            printf("Padre: Hecho!!\n");
            printf("Padre: Esperando a otro hijo...\n");
            wait(NULL);
            printf("Hecho!!\n");
            close(entrada);
            close(salida);
        }
    }
    return 0;
}
