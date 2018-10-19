#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    char leido[100];
    pipe(fd);
    close(fd[1]);
    read(fd[0],leido,100*sizeof(char));
    fprintf(stdout,"%s\n",leido);
    close(fd[0]);
    return 0;
}