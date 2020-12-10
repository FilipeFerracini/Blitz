#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    FILE * arq, *fout;
    tpos vec[1000000];
    ttipo car;
    arq=fopen("base.bin","rb");
    fout=fopen("index.bin","wb");
    fread(&car, sizeof(char),sizeof(ttipo),arq);
    strcpy(vec[0].placa,car.placa);
    vec[0].rrn=1;
    printf("%s %d\n",vec[0].placa,vec[0].rrn);
    for(int i=0;i<5;i++){
        fread(&car, sizeof(char),sizeof(ttipo),arq);
        printf("%s\n", car.placa);
    }
    fclose(arq);
    fclose(fout);

    return 0;
}