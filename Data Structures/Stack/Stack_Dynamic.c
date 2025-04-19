#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 100

typedef struct Stack
{
    int top;
    int capacity;
    int* arr;
}Stack;

//* Additional stacks are created to efficiently track the minimum and maximum values in the main stack.
//* This approach ensures constant time complexity (O(1)) for retrieving the minimum and maximum values.
typedef struct Min_Max{
    int *Min_Array;
    int *Max_Array;
    int Min_Top;
    int Max_Top;
    int Min_Capacity;
    int Max_Capacity;
}Min_Max;



Stack*Create();
int IS_FULL(Stack*S);
int IS_EMPTY(Stack*S);
void Push(Stack*S, int data);
void Double_Size(Stack*S);
void Display(Stack*S);
int Pop(Stack*S);
int Top(Stack*S);
int Size_Stack(Stack*S);
void Merge_Sort(int *arr,int left, int right );
void Merge(int *arr, int left, int mid , int right);
void Clear_All_Stack(Stack*S);
int Binary_Search(Stack*S, int low , int high, int data);
void Reverse_Stack(Stack*S);
void Insert_Bottom(Stack*S, int data);

void Push_2(Stack*S, Min_Max*N,int data);
void Pop_2(Stack*S, Min_Max*N, int data);
void Free_Stack(Stack*S);
void Free_Min_Max(Min_Max*Min);

Min_Max*Create_Min_Max();

void Double_Min(Min_Max*Min);
int Min_Pop(Min_Max*Min);
void Min_Push(Min_Max*Min, int data);
int Min_top(Min_Max*Min);

void Double_Max(Min_Max*Max);
void Max_Push(Min_Max*Max, int data);
int Max_Pop(Min_Max*Max);
int Max_Top(Min_Max*Max);

bool parse_int(char*string, int*integer);

int main(void){
    Stack*S=Create();
    Min_Max*Min= Create_Min_Max();
    char buffer[BUFFER_SIZE];

    int choice, push_value, binary_search;
    bool end_program = true;
    int binary, Popped_value;
    int integer=0; 



    do
    {
        printf("-----------MENU-----------\n");
        printf("------- PUSH - 1 ---------\n");
        printf("--------- POP - 2 --------\n");
        printf("------ TOP ELEMENT - 3 ---\n");
        printf("-------- IS EMPTY - 4 ----\n");
        printf("--------- IS FULL - 5 ----\n");
        printf("--------- SIZE - 6 -------\n");
        printf("--- CLEAR ALL STACK - 7 --\n");
        printf("---- SEARCH IN STACK - 8 -\n");
        printf("--- REVERSE STACK - 9 ----\n");
        printf("--- MIN and MAX - 10 -----\n");
        printf("------ SORTING - 11 ------\n");
        printf("----- DISPLAY - 12 -------\n");
        printf("-------- EXIT - 0 --------\n");
        printf("ENTER YOUR CHOICE HERE ");

        fgets(buffer,BUFFER_SIZE,stdin);
        buffer[strcspn(buffer,"\n")] = '\0';
        if(parse_int(buffer,&integer)){
        switch (integer)
        {
            case  1:
                printf("Value you want to push enter here --> ");
                scanf("%d",&push_value);
                printf("\n");
                Push_2(S,Min,push_value);
                break;
            case 2:
                Popped_value = Pop(S);
                printf("You popped number --> %d\n\n",Popped_value);
                Pop_2(S,Min, Popped_value);
                break;
            case 3:
                printf("Top of Stack --> %d\n\n",Top(S));
                break;
            case 4:
                if (IS_EMPTY(S)){
                    printf("STACK IS EMPTY\n\n");
                }else{
                    printf("STACK IS NOT EMPTY!!!!!\n\n");
                }
                break;
            case 5:
                if(IS_FULL(S)){
                    printf("SORRY for now STACK IS FULL\n\n");
                }else{
                    printf("STACK is not full \n\n");
                }
                break;
            case 6:
                printf("Size of Stack is %d\n\n",Size_Stack(S));
                break;
            case 7:
                Clear_All_Stack(S);
                printf("ALL STACK IS CLEARED \n\n");
                break;
            case 8:
                printf("Enter the value you want yo search in Stack -->");
                scanf("%d",&binary_search);
                Merge_Sort(S->arr, 0 , S->top);
                binary = Binary_Search(S,0 ,S->top-1,binary_search);
                if (binary == -1){
                    printf("SORRY the value you are looking is not in Stack\n\n");
                }else{
                    printf("the Value you are looking is at index %d \n\n",binary);
                }
                break;
            case 9:
                printf("Your stack before reverse\n");
                Display(S);
                printf("after reverse\n");
                Reverse_Stack(S);
                Display(S);
                break;
            case 10:
                if(Min->Min_Top == -1){
                    printf("Minim and Maxim values in Stack are not available (stack is empty)\n\n");
                }
                else{
                    printf("Minim and Maxim Values in Stack \n");
                    printf("Min = %d\n",Min_top(Min));
                    printf("Maxim = %d\n\n",Max_Top(Min));
                }
                break;
            case 11:
                if (IS_EMPTY(S)) {
                    printf("Stack is empty; sorting is not possible.\n\n");
                } else {
                    printf("YOUR UNSORTED STACK IS HERE \n");
                    Display(S);
                    printf("Here is YOUR SORTED STACK \n");
                    Merge_Sort(S->arr, 0, S->top);
                    Display(S);
                }
                break;
            case 12:
                printf("Here is your Stack \n");
                Display(S);
                break;
            case 0:
                printf("THANKS FOR USING MY CODE \n\n");
                printf("Freeing allocated memory\n\n");
                Free_Stack(S);
                Free_Min_Max(Min);
                end_program = false;
                break;
            default:
                printf("PLEASE ENTER A VALID NUMBER and NO STRING!!!\n\n");
                break;
            }
            }
            else{
                printf("please enter valid number\n");
            }
    } while (end_program);
    
    return 0;
}

Stack*Create(){
    Stack*S= malloc(sizeof(Stack));
    if(!S){
        printf("Memory allocation for Stack is failed\n");
        return NULL;
    }
    S->capacity = 1;
    S->top = -1;
    S->arr = malloc(S->capacity*sizeof(int)); // allocate n array of size 1

    if (!S->arr){
        return NULL;
    }
    return S;
}

void Push(Stack*S, int data){
    if (IS_FULL(S)){
        Double_Size(S);
    }
    S->arr[++S->top] = data;
    printf("%d value pushed\n\n",data);
}

void Double_Size(Stack*S){
    S->capacity *=2;
    int *new_arr=realloc(S->arr,S->capacity*sizeof(int));
    if(!new_arr){
        printf("Memory allocation failed\n\n");
        return;
    }
    S->arr=new_arr;
}

int IS_FULL(Stack* S) {
    // Returns 1 if the stack is full, otherwise returns 0
    return S->top == S->capacity - 1;
}

int IS_EMPTY(Stack*S){
    return S->top == -1 ;
}

void Display(Stack*S){
    if (IS_EMPTY(S)){
        printf("Stack is empty\n\n");
        return;
    }
    else{
        for (int i = S->top ; i >= 0 ; i--){
            printf("[%d]\n",S->arr[i]);
        }
        printf("Stack starts here\n");
    }
    printf("\n");
    
}

int Pop(Stack*S){
    if (IS_EMPTY(S) ){
        printf("You can not pop an element, stack is empty\n\n");
        return INT_MIN;
    }
    return S->arr[S->top--];
}

int Top(Stack*S){
    if (IS_EMPTY(S)){     
        printf("Stack is EMPTY\n\n");
        return INT_MIN;
    }
    return S->arr[S->top];
}

int Size_Stack(Stack*S){
    if(IS_EMPTY(S) == 1){
        printf("Stack is empty!!!\n\n");
        return 0;
    }
    return S->top+1;
}

// Divide the array into two subarrays, sort them and merge them
void Merge_Sort(int * arr, int left,int right){
    if (left<right){
    //m is the point where the array is divided into two arrays 
        int mid = left + (right - left)/2;
        Merge_Sort(arr, left , mid );
        Merge_Sort(arr, mid+1, right);
        // Merge the sorted subarrays
        Merge(arr, left , mid , right );
    }
}

// Merge two subarrays L and M into arr
void Merge(int * arr, int left, int mid , int right){
    int l1 = mid - left + 1;
    int l2 = right - mid;

    int *L1=(int*)malloc(l1*sizeof(int));
    int *L2=(int*)malloc(l2*sizeof(int));
    if (!L1 || !L2){
        free(L1);
        free(L2);
        printf("Memory allocation failed!!\n\n");
        return;
    }
    
    for(int i =0 ; i < l1; i++) L1[i] = arr[left +i];
    for(int j =0 ; j < l2; j++) L2[j] = arr[mid + 1 + j];
    // Maintain current index of sub-arrays and main array
    int i,j,k;
    i=0;
    j=0;
    k=left;
    // Until we reach either end of either L or M, pick larger among
    // elements L and M and place them in the correct position at A[p..r]
    while(i<l1 && j< l2){
        if(L1[i]<= L2[j]){
            arr[k] = L1[i];
            i++;
        }else{
            arr[k] = L2[j];
            j++;
        }
        k++;
    }
  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
    while(i<l1) arr[k++] = L1[i++];
    while (j<l2) arr[k++] = L2[j++];
    
    free(L1);
    free(L2);
}

void Clear_All_Stack(Stack*S){
    S->top = -1 ;
}

int Binary_Search(Stack*S, int low ,int high , int data){
    while (low<=high){
        int mid = low  + (high - low )/2;
        if(data == S->arr[mid]){
            return mid;
        }
        if(data > S->arr[mid]){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

void Reverse_Stack(Stack*S){
    if (IS_EMPTY(S)){
        printf("Stack is empty it cannot be reverse\n\n");
        return;
    }
    int temp = Pop(S);
    Reverse_Stack(S);
    Insert_Bottom(S,temp);
}

void Insert_Bottom(Stack*S, int data){
    if (IS_EMPTY(S)){
        Push(S,data);
        return;
    }
    int temp = Pop(S);
    Insert_Bottom(S,data);
    Push(S,temp);
}

Min_Max * Create_Min_Max(){
    Min_Max * Min = malloc(sizeof(Min_Max));
    if (!Min){
        printf("Memory Allocation Failed!!1\n\n");
        return NULL;
    }

    Min->Max_Capacity = 1;
    Min->Max_Top = -1;
    Min->Max_Array = malloc(Min->Max_Capacity * sizeof(int));
    if(!Min->Max_Array) return NULL;

    Min->Min_Capacity = 1;
    Min->Min_Top = -1;
    Min->Min_Array = malloc(Min->Min_Capacity * sizeof(int));
    if(!Min->Min_Array) return NULL;

    return Min;
}
//! min functions here 
void Min_Push(Min_Max*Min, int data){
    if(Min->Min_Top == -1 || Min->Min_Array[Min->Min_Top]> data){
        if(Min->Min_Top == Min->Max_Capacity ){
            Double_Min(Min);
        }
        Min->Min_Array[++Min->Min_Top] = data;
    }
}

void Double_Min(Min_Max*Min){
    Min->Min_Capacity *=2;
    int*arr_min = realloc(Min->Min_Array, Min->Min_Capacity*sizeof(int));
    if (!arr_min){
        printf("Memory Allocation Failed!!\n\n");
        Min->Min_Capacity /=2;
        return;
    }
    Min->Min_Array = arr_min;
}

int Min_Pop(Min_Max*Min){
    if(Min->Min_Top == -1 )
    {
        printf("No Minim element\n\n ");
        return -1;
    }
    return Min->Min_Array[Min->Min_Top--];
}

int Min_top(Min_Max*Min){
    if(Min->Min_Top == -1){
        printf("There is no minim value\n\n");
        return INT_MIN;
    }
    return Min->Min_Array[Min->Min_Top];
}

//! max functions here
void Max_Push(Min_Max*Max, int data){
    if(Max->Max_Top == -1 || Max->Max_Array[Max->Max_Top]< data){
        if(Max->Max_Top == Max->Max_Capacity){
            Double_Max(Max);
        }
        Max->Max_Array[++Max->Max_Top] = data;
    }
}

void Double_Max(Min_Max*Max){
    Max->Max_Capacity *=2;
    int*arr_max = realloc(Max->Max_Array,Max->Max_Capacity*sizeof(int));
    if(!arr_max){
        printf("Memory allocation failed!!!\n\n");
        Max->Max_Capacity /=2;
        return;
    }
    Max->Max_Array = arr_max;
}

int Max_Pop(Min_Max*Max){
    if (Max->Max_Top == -1){
        printf("stack is empty \n\n");
        return INT_MIN;
    }
    return Max->Max_Array[Max->Max_Top--];
}

int Max_Top(Min_Max*Max){
    if (Max->Max_Top == -1){
        printf("Stack is empty\n\n");
        return INT_MIN;
    }
    return Max->Max_Array[Max->Max_Top];
}

void Push_2(Stack*S, Min_Max*N, int data){
    Push(S,data);
    Min_Push(N,data);
    Max_Push(N,data);
}

void Pop_2(Stack*S, Min_Max*N, int data){
    if(!IS_EMPTY(S)){
        if(data == Min_top(N)){
            Min_Pop(N);
        }
        if(data== Max_Top(N)){
            Max_Pop(N);
        }
    }else{
        printf("Stack is empty there is no min max value!!!\n\n");
        return;
    }
}

void Free_Stack(Stack*S){
    free(S->arr);
    free(S);
}

void Free_Min_Max(Min_Max*Min){
    free(Min->Min_Array);
    free(Min->Max_Array);
    free(Min);
}

/**
 * Parses a string to extract an integer value.
 * 
 * @param string The input string to parse.
 * @param integer A pointer to store the parsed integer value.
 * @return true if the string is successfully parsed into an integer, false otherwise.
 */
bool parse_int(char*string, int*integer){

    int i=0;
    while(isspace(string[i])) i++;
    int length = strlen(string);
    if( length == i) return false;

    char integer_buffer[BUFFER_SIZE];
    int integer_chars = 0;

    // Check if the number starts with a negative sign
    if(string[i] == '-'|| string[i]== '+'){
        integer_buffer[integer_chars++] = string[i++];
        if(!isdigit(string[i])) return false;
    }
    // at least one digit should be present 
    if(!isdigit(string[i])) return false; 
    // read digits 
    while(i<length && !isspace(string[i])){
        integer_buffer[integer_chars++] = string[i++];
    }

    integer_buffer[integer_chars] = '\0';

    while(isspace(string[i])) i++;

    if(string[i]!='\0') return false;

    *integer = atoi(integer_buffer);

    return true;
}


