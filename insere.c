#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 1
#define ERROR_MEMORY_FULL 2
#define ERROR_INVALID_POSITION 3
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

typedef struct _node{
    ttipo val;
    struct _node *e;
    struct _node *d;
}tnode;

void listad_cria(tnode ** lista){
    *lista = NULL;
}

int listad_insere_n(tnode ** lista, int pos, ttipo carro){
    int ret = SUCCESS;
    tnode * novo;
    tnode * atual;
    int i;

    novo = (tnode *)malloc(sizeof(tnode));
    if (novo == NULL){
        ret = ERROR_MEMORY_FULL; 
    }else{
        novo->val = carro; 
        if (*lista == NULL){
            novo->e = NULL;
            novo->d = NULL;
            *lista = novo;
        }else if (pos == 0){
            novo->e = NULL;
            novo->d = *lista;
            (*lista)->e = novo;
            *lista = novo;
        }else{
            atual = *lista;
            pos--;
            i = 0;
            while(atual->d != NULL){
                if (i < pos){
                    atual = atual->d;
                    i++;
                }else{
                    break;
                }
            }
            if (i!=pos){ /* posicao incorreta*/
                ret = ERROR_INVALID_POSITION;
            }else{
                /*insercao a direita*/
                novo->e = atual;
                novo->d = atual->d;
                if (atual->d != NULL)
                    atual->d->e = novo;
                atual->d = novo;
            }
        }
    }
    printf("carro %s %d %s %s %s foi roubado!\n", carro.placa,carro.ano,carro.marca,carro.modelo,carro.estado);
    return ret;
}

int consulta(tnode **lista, char placa[]){
    int ret=ERROR_INVALID_POSITION;
    tnode *atual;
    atual = *lista;
    if (*lista == NULL){
        ret = ERROR_INVALID_POSITION;
    }else{
            while(strcmp(atual->val.placa,placa)){
                if (atual->d == NULL)
                    break;
                else
                    atual = atual->d;
            }
            if(strcmp(atual->val.placa,placa)==0)
                ret=SUCCESS;
    }
    if(ret==SUCCESS)
        printf("carro %s %d %s %s %s eh roubado!\n", atual->val.placa,atual->val.ano,atual->val.marca,atual->val.modelo,atual->val.estado);
    else
        ret=ERROR_INVALID_POSITION;

    return ret;
}

int main (void){
    char input,placa[8];
    tnode *lista;    
    listad_cria(&lista);
    tpos vec[MAX];
    int tam=0;
    FILE *index, *base;
    index=fopen("index.bin","rb");
    base=fopen("base.bin","rb");

    for(int i=0;i<MAX;i++)
        fread(&vec[i], sizeof(char),sizeof(tpos),index);

    while((scanf("%c %s ",&input,placa))==2 && tam<100){
        ttipo car;
        int achou=-1;
        if(input=='r'){
            strcpy(car.placa,placa);
            scanf("%d %s %s %s ",&car.ano,car.marca,car.modelo,car.estado);
            listad_insere_n(&lista,0,car);
            tam++;
        }else if(input=='c'){
            achou=consulta(&lista,placa);
            if (achou==ERROR_INVALID_POSITION){
                achou=vec[buscabinrec(vec,placa,0,MAX-1)].rrn-1;
                if(achou==-1)
                    printf("carro %s nao consta na lista\n",placa);
                else{
                    fseek(base,achou*sizeof(ttipo),SEEK_SET);
                    fread(&car,sizeof(char),sizeof(ttipo),base);
                    printf("carro %s %d %s %s %s eh roubado!\n",car.placa,car.ano,car.marca,car.modelo,car.estado);
                }
            }
        }
    }
    fclose(index);
    fclose(base);
    
    return 0;
}