#include <stdio.h>

int main(int argc, char const *argv[])
{
    fprintf(stdout, "Escribe un nombre para saludar: ");
    char nombre[15];
    fscanf(stdin,"%s",nombre);
    fprintf(stdout,"Hola %s.\nTu inicial es %c\n",nombre,nombre[0]);
    return 0;
}
