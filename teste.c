#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000001

typedef struct{
    char placa[8];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
}ttipo;

typedef struct{
    char placa[8];
    int rrn;
}tpos;

int main(void){
    FILE * arq;
    tpos aux;
    int i;
    arq=fopen("index.bin","rb");

    for(i=0;i<MAX;i++){
        fread(&aux,sizeof(char),sizeof(tpos),arq);
        printf("%s %d\n",aux.placa,aux.rrn);
    }

    fclose(arq);    

    return 0;
}