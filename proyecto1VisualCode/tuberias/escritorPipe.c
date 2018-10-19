#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char* frase = "Hola soy el escritor";
    int fd[2];
    pipe(fd);
    close(fd[0]);
    long int caracteresEscritos = write(fd[1],frase,strlen(frase)*sizeof(char));
    fprintf(stdout,"He escrito: %ld\n",caracteresEscritos);
    close(fd[1]);
    return 0;
}
