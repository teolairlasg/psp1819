#include <stdio.h>
#include <string.h>
#include <errno.h>


int main(int argc, char const *argv[])
{
    FILE* fichero;

    fichero = fopen("./hola.txt","r");
    if(fichero == NULL){
        perror("Error abriendo el fichero");
        fprintf(stderr,"Error""%s: línea %d: Código de error %d. Texto: %s\n",
                __FILE__,__LINE__,errno,strerror(errno));
        exit(-1);
    }
    return 0;
}
