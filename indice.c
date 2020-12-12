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

void troca(tpos *a, tpos *b){
    tpos aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int separa(tpos *v, int comeco, int fim){
    tpos pivo=v[fim];
    int j=comeco,k;
    for(k=comeco;k<fim;k++){
        if(strcmp(v[k].placa,pivo.placa)<=0){
            troca(&v[k],&v[j]);
            j++;
        }
    }
    troca(&v[j],&v[fim]);
    return j;
}

void quicksort(tpos *v,int comeco, int fim){
    int pivo;
    if(comeco<fim){
        pivo=separa(v,comeco,fim);
        quicksort(v,comeco,pivo-1);
        quicksort(v,pivo+1,fim);
    }
}

int main(void){
    FILE * arq, *fout;
    tpos vec[MAX];
    ttipo car;
    int i;
    arq=fopen("base.bin","rb");
    fout=fopen("index.bin","wb");

    for(i=0;i<MAX;i++){
        fread(&car, sizeof(char),sizeof(ttipo),arq);
        strcpy(vec[i].placa,car.placa);
        vec[i].rrn=i+1;
    }

    quicksort(vec,0,MAX-1);
    
    for(i=0;i<MAX;i++)
        fwrite(&vec[i],sizeof(char), sizeof(tpos),fout);

    fclose(arq);
    fclose(fout);

    return 0;
}