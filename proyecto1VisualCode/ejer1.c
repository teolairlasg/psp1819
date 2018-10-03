#include <stdio.h>

int main(int argc, char const *argv[])
{
    FILE* fichero = fopen("./ejer1.txt","w");
    char texto[100];
    fprintf(stdout, "Escribe un mensaje: ");
    scanf("%s",texto);
    fwrite(texto,4,sizeof(char),fichero);
    putc('\n',fichero);
    fclose(fichero);
    return 0;
}
