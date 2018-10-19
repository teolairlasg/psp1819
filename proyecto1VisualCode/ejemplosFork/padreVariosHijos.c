#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if(argc != 2){
        printf("Uso del programa:\n\t %s num_hijos\n",argv[0]);
        exit(-1);
    }
    int num_hijos = atoi(argv[1]);
    int pid_hijo;
    for(int i = 0; i<num_hijos;i++){
        pid_hijo = fork();
        if (pid_hijo == 0){
            printf("HIJO %3d: mi pid %d\n",i,getpid());
            return 0;
        }
    }
    for(int i = 0; i<num_hijos;i++){
        wait(NULL);
        printf("PADRE: Un hijo ha acabado.\n");
    }
    return 0;
}
