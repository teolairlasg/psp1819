#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <string.h>
#define MAX 6

int getIndexElement(char*, char*[],int);
void recibirNota(int,char*);
void enviarNota(int,char*);

int main(){
    char* escala[]={"Do","Do#","Re","Re#","Mi","Fa","Fa#","Sol","Sol#","La","La#","Si"};
    int nElems = sizeof(escala)/sizeof(escala[0]);
    char leido[MAX];
    int pipePadH1[2], pipePadH2[2], pipeH1Pad[2], pipeH2Pad[2];
    pipe(pipeH1Pad); pipe(pipeH2Pad);
    pipe(pipePadH1); pipe(pipePadH2);
    pid_t pidH1 = fork();
    if (pidH1 == 0){//Hijo calculará la 2ª nota
        char nota[MAX];
        //Cerramos lo que no necesitamos.
        close(pipePadH1[1]);close(pipeH1Pad[0]);
        recibirNota(pipePadH1[0],nota);
        int indice=(getIndexElement(nota,escala,nElems)+4)%nElems;
        enviarNota(pipeH1Pad[1],escala[indice]);
    }else{
        pid_t pidH2 = fork();
        if (pidH2 == 0){ //Hijo 2 calculará la 3ª nota
            char nota[MAX];
            //Cerramos lo que no necesitamos.
            close(pipePadH2[1]);close(pipeH2Pad[0]);
            recibirNota(pipePadH2[0],nota);
            int indice=(getIndexElement(nota,escala,nElems)+7)%nElems;
            enviarNota(pipeH2Pad[1],escala[indice]);
        }else{ //Código del padre
            //Cerramos lo que no necesitamos.
            close(pipePadH1[0]);close(pipePadH2[0]);
            close(pipeH1Pad[1]);close(pipeH2Pad[1]);
            do{
                printf("Escribe una nota correcta: ");
                fgets(leido,MAX,stdin);
                leido[strlen(leido)-1]='\0';
            }while(getIndexElement(leido,escala,nElems)==-1);
            enviarNota(pipePadH1[1],leido);
            enviarNota(pipePadH2[1],leido);
            char nota2[MAX],nota3[MAX];
            recibirNota(pipeH1Pad[0],nota2);
            recibirNota(pipeH2Pad[0],nota3);
            wait(NULL);wait(NULL);
            printf("El acorde de %sM es: %s - %s - %s\n",leido,leido,nota2,nota3);
        }
    }
    return 0;
}

void recibirNota(int pipe,char* nota){
    read(pipe,nota,MAX);
}

void enviarNota(int pipe,char* nota){
    write(pipe,nota,MAX);
}

int getIndexElement(char* cadenaBuscada, char* array[], int nElems){
    bool encontrado = false;
    int retorno = -1;
    for(int i = 0; (i < nElems && !encontrado); i++){
        if(strcmp(array[i],cadenaBuscada)==0){
            encontrado=true;
            retorno=i;
        }    
    }
    return retorno;
}