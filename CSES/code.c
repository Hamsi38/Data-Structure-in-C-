#include <stdio.h>
#include <stdlib.h>


int main(void){
    FILE*fp = fopen("fred.txt", "r");
    if(fp == NULL){
        printf("cannot open fred.txt \n\n",stderr);
        return EXIT_FAILURE;
    }
    

    return 0;
}