#include <stdio.h>
#include <string.h>

int main(void){

    printf("%d\n", strcmp("c AAB5825","c AAB5825"));
    printf("%d\n", strcmp("c AAB5825","c AAB1162"));
    printf("%d\n", strcmp("c AAB5825","c AAB4942"));
    printf("%d\n", strcmp("c AAB5825","c AAB4994"));
    printf("%d\n", strcmp("c AAB5825","c AAB4994"));
    printf("%d\n", strcmp("c AAB5825","c AAB5990"));
    printf("%d\n", strcmp("c AAB5825","c AAB3302"));
    printf("%d\n", strcmp("c AAB5825","c AAB4985"));
    printf("%d\n", strcmp("c AAB5825","c AAB3236"));


    return 0;
}