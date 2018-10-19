#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;
    fprintf(stdout,"Soy el proceso principal mi pid es: %d\n\n",getpid());
    
    pid = fork();
    if (pid == -1){
        fprintf(stderr,"Error");
        exit(-1);
    }
    if(pid == 0){  //Código del hijo
        printf("Soy el proceso hijo mi pid es: %d\n",getpid());
        sleep(1);
    }else{  //Código del padre
        printf("Soy el proceso padre mi pid es: %d, el hijo que he creado es %d\n",getpid(),pid);
        wait(NULL);
        printf("El hijo ha acabado.\n");
        return 0;
    }
    
}
