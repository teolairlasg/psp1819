#include <stdio.h>

int main(int argc, char const *argv[])
{
    fprintf(stdout, "Escribe un número: ");
    int entero;
    fscanf(stdin,"%d",&entero);
    fprintf(stdout,"El número es %d y se encuentra en %ld",entero,&entero);
    return 0;
}
