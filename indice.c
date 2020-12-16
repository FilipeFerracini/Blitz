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

void intercala(tpos *v, int comeco, int meio, int fim){
    tpos w[2*fim];
    int i,j,k=0;
    i=comeco;
    j=meio;
    while(i<meio && j<fim){
        if(strcmp(v[i].placa,v[j].placa)<0){
            w[k]=v[i];
            i++;
        }else{
            w[k]=v[j];
            j++;
        }
        k++;
    }
    while(i<meio){
        w[k]=v[i];
        i++;
        k++;
    }
    while(j<fim){
        w[k]=v[j];
        j++;
        k++;
    }
    for(i=comeco;i<fim;i++)
        v[i]=w[i-comeco];
}

void mergesort( tpos *v, int comeco,int fim){
    int meio;
    if(comeco<fim-1){
        meio=(comeco+fim)/2;
        mergesort(v,comeco,meio);
        mergesort(v,meio,fim);
        intercala(v,comeco,meio,fim);
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

    mergesort(vetor,0,n);
    
    for(i=0;i<n;i++)
        fwrite((vetor+i),sizeof(char), sizeof(tpos),fout);

    fclose(arq);
    fclose(fout);
    free(vetor);

    return 0;
}