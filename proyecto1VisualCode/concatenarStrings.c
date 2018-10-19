#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprimirHolaMundo();
void imprimirEnteroyCaracter(int,char);
void imprimrASCIIhasta(char, int);

int main(int argc, char const *argv[])
{
    char cad1[]="Hola";
    char cad2[]="-";
    char cad3[]="mundo.";
    //tamTotal es el total de todas las cadenas más el \0 de final.
    int tamTotal=strlen(cad1)+strlen(cad2)+strlen(cad3)+1;
    char *cadRes = (char*)malloc(tamTotal*sizeof(char));

    imprimirHolaMundo();
    imprimirEnteroyCaracter(45,'J');

    cadRes=strcat(cadRes,cad1);
    cadRes=strcat(cadRes,cad2);
    cadRes=strcat(cadRes,cad3);

    fprintf(stdout,"%s\n",cadRes);
    imprimrASCIIhasta('Z',6);

    return 0;
}

void imprimirHolaMundo(){
    fprintf(stdout,"Hola mundo\n");
}

void imprimirEnteroyCaracter(int a, char b){
    fprintf(stdout,"Me has dicho que imprima el entero %d y el carácter %c\n",a,b);
}

void imprimrASCIIhasta(char limite, int columnas){
    for(int i = 0; i<=limite;i+=columnas){
        fprintf(stdout,"\n| ");
        for(int j=0;j<=(j%columnas);j++){
            fprintf(stdout," %3d --> %c |",i+j,i+j);
        }
    }
    fprintf(stdout,"\n| ");
}