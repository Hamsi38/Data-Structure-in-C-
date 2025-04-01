#include <stdio.h>
#include <stdlib.h>

int main(){


    int size=10;
    char*arr=(char*)malloc(size*sizeof(char));
    if (arr==NULL)
    {
        printf("failed\n");
        return 1;
    }
    
    

    return 0;
}