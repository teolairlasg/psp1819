#include <stdio.h>

void main(int argc, char const *argv[])
{
    
    for(int i = 1; i < argc; i++)
    {
        printf("Hola %s.\n",argv[i]);
    }
    
}
