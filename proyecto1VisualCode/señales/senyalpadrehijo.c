#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void tratarSIGINT(int);
int main(int argc, char const *argv[])
{
    
    pid_t pid;
    signal(SIGINT,tratarSIGINT);
    pid=fork();
    if (pid == -1){
        perror("Error en el fork");
        exit(-1);
    }
    if(pid == 0){ //Soy el hijo
        sleep(2);
        printf("HIJO: pid: %d\n",getpid());
        if( kill(getppid(),SIGINT) ==-1 )
            perror("HIJO: Error en el kill");
    }else{ //Soy el padre
       printf("PADRE: pid: %d\n",getpid());
       pause();
    }
    return 0;
}

void tratarSIGINT(int codSenyal){
    printf("Soy el proceso %d me han enviado una señal\n",getpid());
}