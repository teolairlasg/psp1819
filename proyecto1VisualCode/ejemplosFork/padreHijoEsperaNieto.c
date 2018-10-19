#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    printf("PROCESO_INICIAL\n\tmi pid es: %d\n\tmi padre es: %d\n",getpid(),getppid());
    pid = fork();
    if (pid == -1){
        fprintf(stderr,"Error");
        exit(-1);
    }
    if(pid == 0){  //Código del hijo
        printf("HIJO:\n\tmi pid es: %d\n\tmi padre es: %d\n",getpid(),getppid());
        pid_t pidNieto = fork();
        if(pidNieto == -1 ){exit(-1);}
        if(pidNieto == 0){ //Soy el Nieto
            printf("NIETO:\n\tmi pid es: %d\n\tmi padre es: %d\n",getpid(),getppid());
            sleep(3);
        }else{ //Vuelvo a ser el hijo
            printf("HIJO: Esperando al nieto...\n");
            wait(NULL);  //Espero a mi hijo, que es el nieto de mi padre.
            printf("HIJO: El nieto ha acabado.\n");
            sleep(1);
        }
    }else{  //Código del padre
        printf("PADRE: %d, el hijo que he creado es %d\n",getpid(),pid);
        wait(NULL); 
        printf("PADRE: El hijo ha acabado.\n");
    }
    return 0;
}
