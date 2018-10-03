#include<stdio.h>

int main(int argc, char const *argv[])
{
    int entero = 135689;
    FILE* fichero = fopen("./escribirEntero.txt","wb");
    fwrite(&entero,sizeof(int),1,fichero);
    return 0;
}
