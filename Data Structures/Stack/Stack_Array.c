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
void Push(Stack*S, int data, int *minStack, int *maxStack, int *minTop, int* maxTop);
int Pop(Stack*S, int *minStack, int *maxStack, int *minTop, int *maxTop);
void Delete_Stack(Stack*S);
int Top(Stack*S);
int Size_Stack(Stack*S);
void Display(Stack*S);
int Binary_Search(Stack*S, int value,int low ,int high);
void merge(int *arr, int low , int mid ,int high);
void mergeSort(int *arr, int left ,int right);
void Reverse(Stack*S);
int Max_Stack_Top(int *maxStack, int maxTop);
int Min_Stack_Top(int *minStack, int minTop);


int main(int argc, char *argv[]){
    Stack*S=CreateStack();
    int choice,push_val,search_val,searchTemp;
    bool con=true;
    int minStack[MAXSIZE];
    int maxStack[MAXSIZE];
    int minTop = -1;
    int maxTop = -1;


    do
    {   
        printf("----------WELCOME TO ARRAY STACK------ \n");
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
            Push(S, push_val , minStack, maxStack, &minTop, &maxTop);
            break;
        case 2:
            printf("the Value you popped is %d\n\n",Pop(S ,minStack ,maxStack ,&minTop, &maxTop));
            break;
        case 3:
            printf("Top of the Stack is %d\n\n",Top(S));
            break;
        case 4:
            if (isStackEmpty(S))
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
        case 8:
            printf("Enter the Element you want to search in Stack ");
            scanf("%d",&search_val);
            printf("\n");
            searchTemp=Binary_Search(S,search_val ,0 ,S->top);
            if (searchTemp == -1 )
            {
                printf("the Element you are looking is not in the Stack SORRY!!!\n\n");
            }
            else
            {
                printf("the Value you entered is at index %d\n\n",searchTemp);
            }
            break;
        case 9:
            printf("Here is your Stack before Reversing\n");
            Display(S);
            printf("\n");
            Reverse(S);
            Display(S);
            break;
        case 10:
            printf("Here is your Max and Min Numbers in Stack\n");
            printf("Current Max Number %d\n",Max_Stack_Top(maxStack, maxTop));
            printf("Current Min Number %d\n\n",Min_Stack_Top(minStack, minTop));
            break;
        case 11:
            printf("Here is your sorted Stack\n");
            mergeSort(S->arr,0,S->top);
            Display(S);
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

void Push(Stack*S,int data, int *minStack, int *maxStack , int *minTop, int* maxTop){
    if (isStackFull(S)){
        printf("Stack is overflow\n\n");
        return;
    }
        S->arr[++S->top]=data;
        //*for better time complexity i made like this if you want  you can ma ke linear search in Stack array but O(n) time 
        if(*minTop == -1 || data <= minStack[*minTop]){//! it is not gonna update the minTop and maxTop because they are local variables here we are derefrecing here with pointer update the integers 
            minStack[++(*minTop)]=data;
        }
        if (*maxTop == -1 || data >= maxStack[*maxTop]){
            maxStack[++(*maxTop)]=data;
        }
        
        printf("Pushed with Success %d\n\n",data);
}

int Pop(Stack*S, int * minStack, int *maxStack, int *minTop, int* maxTop){
    if (isStackEmpty(S))
    {
        printf("Stack is Empty you can't push\n\n");
        return INT_MIN;
    }

    int popped = S->arr[S->top--];

    if (S->arr[S->top] ==maxStack[(*maxTop)]){
        (*maxTop)--;
    }
    if (S->arr[S->top] ==minStack[(*minTop)]){
        (*minTop)--;
    }
    
    return popped;
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

int Binary_Search(Stack*S, int value,int low, int high){
    while (low<=high)
    {
        int mid =low+(high-low)/2;
        if (value==S->arr[mid]) return mid;
        if (value>S->arr[mid]) low = mid+1;
        else high = mid-1;
    }
    return -1;    
}

void merge(int *arr, int left ,int mid ,int right){
    int l1 = mid - left+1;
    int l2 = right-mid;

    printf("merge: left = %d, mid = %d, right = %d, l1 = %d, l2 = %d\n\n",left ,mid , right ,l1 , l2);
    // dynamically allocate to track the merge for the subarrays 
    int *arrLeft =(int *)malloc(l1*sizeof(int));
    int *arrRight = (int *)malloc(l2*sizeof(int));

    for(int i=0 ; i < l1;i++) arrLeft[i] = arr[left + i];
    for(int j=0 ; j < l2;j++) arrRight[j] = arr[mid + 1 + j];

    int i=0, j=0, k=left;
    while (i<l1 && j<l2)
    {
        if (arrLeft[i]<=arrRight[j]) arr[k++]= arrLeft[i++];
        else arr[k++]= arrRight[j++];
        
    }
    while (i<l1) arr[k++] = arrLeft[i++];
    while (j<l2) arr[k++] = arrRight[j++];

    free(arrLeft);
    free(arrRight);
}

void mergeSort(int *arr, int left , int right){
    if (left < right){
        int mid = left + (right - left)/2;
        mergeSort(arr,left,mid);
        mergeSort(arr,mid+ 1, right);
        merge(arr,left ,mid , right);
    }    
}

void Reverse(Stack*S){
    int *stk = (int*)malloc((S->top + 1) * sizeof(int));
    if (stk == NULL){
        printf("Memory allocation failed for reversing the stack\n\n");
        return;
    }

    int j = 0;
    for (int i = S->top; i >= 0; i--){
        stk[j++] = S->arr[i];
    }

    for (int i = 0; i <= S->top; i++){
        S->arr[i] = stk[i];
    }

    free(stk);
    printf("Stack reversed successfully\n\n");
}

int Min_Stack_Top(int *minStack, int mintop){
    if(mintop == -1){
        return -1;
    }
    return minStack[mintop];
}

int Max_Stack_Top(int *maxStack, int maxtop){
    if (maxtop == -1 ){
        return -1;
    }
    return maxStack[maxtop];
}


