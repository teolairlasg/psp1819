#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char leido[100];
    int descLectura;
    descLectura = open("./tuberia",O_RDONLY);
    read(descLectura,leido,100*sizeof(char));
    fprintf(stdout,"%s\n",leido);
    close(descLectura);
    return 0;
}