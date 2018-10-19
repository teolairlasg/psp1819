#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char* frase = "Hola soy el escritor";
    int descriptorEscritura;
    descriptorEscritura = open("./tuberia",O_WRONLY);
    fprintf(stdout,"He escrito: %ld\n",
        write(descriptorEscritura,frase,strlen(frase)*sizeof(char)));

    close(descriptorEscritura);
    return 0;
}
