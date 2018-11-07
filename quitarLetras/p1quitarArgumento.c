#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 4 && argc != 3){
        fprintf(stderr,"Error en el número de argumentos.\n");
        fprintf(stderr,"Uso:\n\t %s fichero_origen letra [fichero_destino].\n",argv[0]);
        fprintf(stderr,"Si no se especifica, fichero_destino sobrescribirá ./salida.txt.\n");
        exit(-1);
    }
    char cBorrar = argv[2][0];
    char fnSalida[] ="salida.txt";
    
    printf("Fichero de entrada: %s.\n",argv[1]);
    printf("Caracter que se eliminará: %c.\n",cBorrar);
    printf("Fichero de salida: %s.\n",fnSalida);

    FILE * fEntrada;
    FILE * fSalida;

    fEntrada = fopen(argv[1],"r");
    fSalida = fopen(fnSalida,"w");

    char c;
    while ((c=getc(fEntrada))!=EOF){
        if(c!=cBorrar){
            putc(c,fSalida);
        }
    }
    fclose(fEntrada);
    fclose(fSalida);
    
    return 0;
}
