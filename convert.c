#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char placa[8];
    int ano;
    char marca[10];
    char modelo[15];
    char estado[3];
}ttipo;

int main(void){

    FILE *file, *fout;
    file=fopen("base.txt", "r");
    fout=fopen("base.bin","wb");
    ttipo car;
    char input;
    while(!feof(file)){
        fscanf(file, "%c %s %d %s %s %s ", &input, car.placa, &car.ano, car.marca, car.modelo, car.estado);
        fwrite(&car,sizeof(char), sizeof(ttipo),fout);
    }
    fclose(file);
    fclose(fout);

    return 0;
}