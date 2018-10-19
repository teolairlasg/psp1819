
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    printf("hola\n");
    fflush(stdout);
    fork();
    printf("hola2\n");
    fflush(stdout);
    
    return 0;
}
