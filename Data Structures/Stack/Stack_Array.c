#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAXSIZE 100


typedef struct Stack
{
    int top;
    int capacity;
    int *arr;
}Stack;

Stack*CreateStack();
int isStackEmpty(Stack*S);
int isStackFull(Stack*S);
void Push(Stack*S,int data);
int Pop(Stack*S);
void Delete_Stack(Stack*S);
int Top(Stack*S);
int Size_Stack(Stack*S);
void Display(Stack*S);


int main(){
    Stack*S=CreateStack();
    int choice,push_val;
    bool con=true;

    do
    {   
        printf("----------WELCOME TO ARRAY STACK----------- \n");
        printf("---------- Push element into Stack - 1\n");
        printf("---------- Pop element from Stack  - 2\n");
        printf("---------- Top element of Stack    - 3\n");
        printf("----------     is Empty ?  --------- 4\n");
        printf("----------     is FULL ------------- 5\n");
        printf("----------     Size -----------------6\n");
        printf("----------     Clear all Stack ------7\n");
        printf("----------  Search in Stack ---------8\n");
        printf("---------- Reverse the Stack-------- 9\n");
        printf("---------- Find Min and Max of Stack-10\n");
        printf("---------- Sort the Stack------------11\n");
        printf("---------- Display the Stack --------12\n");
        printf("----------       EXIT - 0    ----------\n");
        printf("Enter your Choice ");
        scanf("%d",&choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            printf("Enter the Value you want to push into Stack ");
            scanf("%d",&push_val);
            Push(S,push_val);
            break;
        case 2:
            printf("the Value you popped is %d\n\n",Pop(S));
            break;
        case 3:
            printf("Top of the Stack is %d\n\n",Top(S));
            break;
        case 4:
            if (isStackEmpty(S)==-1)
            {
                printf("Stack is empty\n\n");
            }else
            {
                printf("Stack is not empty\n\n");
            }
            break;
        case 5:
            if (isStackFull(S)==1)
            {
                printf("Stack is full\n\n");
            }else
            {
                printf("Stack is not full\n\n");
            }
            break;
        case 6:
            printf("Size of Stack is %d\n\n",Size_Stack(S));
            break;
        case 7:
            Delete_Stack(S);
            break;
        case 12:
            printf("Here is your Stack\n\n");
            Display(S);
            break;
        case 0:
            printf("THANKS FOR USING MY PROGRAM\n\n");
            con=false;
            break;
        default:
            printf("PLEASE ENTER A VALID CHARACTER\n\n");
            break;
        }
    } while (con);
    
    return 0;
}

Stack*CreateStack(){
    Stack*S=malloc(sizeof(Stack));
    if (!S)
    {
        printf("MEMORY ALLOCATION FAILED FOR STACK!!!\n\n");
        return NULL;
    }
    S->capacity=MAXSIZE;
    S->top=-1;
    S->arr=(int*)malloc(S->capacity*sizeof(int));
    if(!S->arr){
        printf("MEMORY ALLOCATION FAILED FOR STACK\n\n");
        free(S->arr);// prevent memory leak
        return NULL;
    }
    return S;
}

int isStackEmpty(Stack*S){
    return (S->top == -1);// if condition is true it is gonna return 1 if it is not 0
}

int isStackFull(Stack*S){
    return (S->top==S->capacity-1);// if condition is true return 1 or false return 0
}

void Push(Stack*S,int data){
    if (isStackFull(S)){
        printf("Stack is overflow\n\n");
        return;
    }
        S->arr[++S->top]=data;
        printf("Pushed with Success %d\n\n",data);
}

int Pop(Stack*S){
    if (isStackEmpty(S))
    {
        printf("Stack is Empty you can't push\n\n");
        return INT_MIN;
    }
    return S->arr[S->top--];
}

void Delete_Stack(Stack*S){
    if(S==NULL){
        printf("Stack is already NULL\n\n");
        return;
    }
    free(S->arr);
    S->arr=NULL;
    S->top=-1;
    printf("You deleted all elements in Stack\n\n");
    free(S);
}

int Top(Stack*S){
    if (isStackEmpty(S)){
        return INT_MIN;
    }
    return S->arr[S->top];
}

int Size_Stack(Stack*S){
    return S->top+1;
}

void Display(Stack*S){
    if (isStackEmpty(S)||S==NULL)
    {
        printf("There nothing Display because Stack is empty\n");
        return;
    }
    else
    {
        for (int i = S->top; i>-1; i--)
        {
            printf("[%d]\n",S->arr[i]);
        }
        printf("Down of Stack\n");
    }
    printf("\n\n");
}


