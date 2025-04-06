#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Stack
{
    int top;
    int capacity;
    int* arr;
}Stack;

Stack*Create();


int main(){
    Stack*S=Create();

    return 0;
}

Stack*Create(){
    
}