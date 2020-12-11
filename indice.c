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

void troca(int *a, int *b){
    int aux;
    aux=*a;
    *a=*b;
    *b=aux;
}

int separa(int *v, int comeco, int fim){
    int pivo=v[fim];
    int j=comeco,k;
    for(k=comeco;k<fim;k++){
        if(v[k]<=pivo){
            troca(&v[k],&v[j]);
            j++;
        }
    }
    troca(&v[j],&v[fim]);
    return j;
}

void quicksort(int *v,int comeco, int fim){
    int pivo;
    if(comeco<fim){
        pivo=separa(v,comeco,fim);
        quicksort(v,comeco,pivo-1);
        quicksort(v,pivo+1,fim);
    }
}

int main(void){
    FILE * arq, *fout;
    tpos vec[1000001];
    ttipo car;
    int i;
    arq=fopen("base.bin","rb");
    fout=fopen("index.bin","wb");

    for(i=0;i<=1000000;i++){
        fread(&car, sizeof(char),sizeof(ttipo),arq);
        strcpy(vec[i].placa,car.placa);
        vec[i].rrn=i+1;}
        
    i--;
    fclose(arq);
    fclose(fout);
    printf("%d\n",i);
    printf("%s %d\n",vec[0].placa,vec[0].rrn);
    printf("%s %d\n",vec[i].placa,vec[i].rrn);
    return 0;
}