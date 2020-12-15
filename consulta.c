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

int buscabinrec(tpos v[],char x[], int inf,int sup){
    int meio=(inf+sup)/2;
    int ret=-1;
    if(strcmp(v[meio].placa,x)==0)
        ret=meio;
    else{
        if(inf<sup){
            if(strcmp(x,v[meio].placa)>0)
                ret=buscabinrec(v,x,meio+1,sup);
            else
                ret=buscabinrec(v,x,inf,meio-1);
        }
    }
    return ret;
}

int main(void){
    FILE *index, *base;
    tpos *vetor;
    char input,placa[8];
    ttipo car;
    index=fopen("index.bin","rb");
    base=fopen("base.bin","rb");

    fseek(index, 0, SEEK_END);
    long lpos = ftell(index);
    int n = lpos / sizeof(tpos);

    vetor = (tpos *) malloc(n * sizeof(tpos));
    fseek(index, 0, SEEK_SET);
    for(int i=0;i<n;i++)
        fread((vetor+i), sizeof(char),sizeof(tpos),index);
    
    while(scanf("%c %s ", &input, placa)==2){
        if(input=='c'){
            int pos=0;
            pos=(vetor+buscabinrec(vetor,placa,0,n-1))->rrn-1;
            if(pos==-1)
                printf("carro %s nao consta na lista\n",placa);
            else{
                fseek(base,pos*sizeof(ttipo),SEEK_SET);
                fread(&car,sizeof(char),sizeof(ttipo),base);
                printf("carro %s %d %s %s %s eh roubado!\n",car.placa,car.ano,car.marca,car.modelo,car.estado);
            }
        }
    }
    fclose(index);
    fclose(base);
    free(vetor);

    return 0;
}