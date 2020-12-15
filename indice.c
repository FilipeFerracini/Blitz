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
    tpos *vetor;
    ttipo car;
    int i;
    arq=fopen("base.bin","rb");
    fout=fopen("index.bin","wb");
    
    fseek(arq, 0, SEEK_END);
    long lpos = ftell(arq);
    int n = lpos / sizeof(ttipo);

    vetor = (tpos *) malloc(n * sizeof(tpos));
    for(i=0;i<n;i++){
        fseek(arq,i*sizeof(ttipo),SEEK_SET);
        fread(&car, sizeof(char),sizeof(ttipo),arq);
        strcpy((vetor+i)->placa,car.placa);
        (vetor+i)->rrn=i+1;
    }

    quicksort(vetor,0,n-1);
    
    for(i=0;i<n;i++)
        fwrite((vetor+i),sizeof(char), sizeof(tpos),fout);

    fclose(arq);
    fclose(fout);
    free(vetor);

    return 0;
}