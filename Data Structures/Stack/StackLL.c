#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define WHITE "\033[1;37m"
#define RED "\033[1;31m"
#define RESET "\033[0m"

#define BUFFER_SIZE 100

typedef struct StackNode
{
    int data;
    struct StackNode*next;
}StackNode;

typedef struct Stack
{
    StackNode*top;
    int size;
}Stack;


// we can't put isfull function because this is Stack is based on Linked list 

// these are basic functions checking the value entered is integer or not
//Display of our stack and Menu bar
StackNode*Node_Maker(int data);
void push(Stack*stack, int data);
int pop(Stack*stack);
bool isEmpty(Stack*stack);
bool topEl(Stack*stack, int* topElement);

void Clear(); 
void Menu();
bool parse_int(char*String, int *choice);
void Display(Stack*head);



int main(void){
    Stack stack = {NULL,0};
    int choice, push_value, search_value, topElement = 0;
    char buffer[BUFFER_SIZE];
    bool parse_condition, end_program = true, is_empty;

    do
        {
        Menu();
        printf("Enter Your Answer Here --> ");
        fgets(buffer,BUFFER_SIZE,stdin);
        parse_condition = parse_int(buffer,&choice);

        if(parse_condition){
            switch (choice)
                {
                case 1:
                    printf("Enter your value to insert into stack : ");
                    scanf("%d",&push_value);
                    Clear();
                    push(&stack ,push_value);
                    break;
                case 2:
                    printf(BLUE"------------\nHere is your Popped Value from Stack -->%d\n\n"RESET,pop(&stack));
                    break;
                case 3:
                    if(topEl(&stack, &topElement)){
                        printf(WHITE"Here is your Top element -->%d\n\n"RESET,topElement);
                    }
                    break;
                case 4:
                    is_empty = isEmpty(&stack);
                    if(is_empty){
                        printf("stack is empty insert element\n\n");
                    }
                    else if (!is_empty)
                    {
                        printf("Stack is not empty\n\n");
                    }
                    break;
                case 5:
                    printf("Size of Stack is --> %d\n",stack.size);
                    break;

                case 11:
                    printf(WHITE"Here is your Stack based on LinkedList\n"RESET);
                    Display(&stack);
                    break;
                case 0:
                    printf(RED"Thx for using my program have a good day \n\n"RESET);
                    end_program = false;
                    break;

                default:
                    printf(RED"Please enter a number between 1 - 12 (include 1 and 12)\n and if you want to exit from program just enter 0\n\n "RESET);
                    break;
                }
        }
        else{
            printf(RED"---------------------------------\n");
            printf("INVALID INPUT PLEASE TRY AGAIN!!!\n");
            printf("---------------------------------\n\n"RESET);
        }
    } while (end_program);
    return 0;
    }


void Menu(){
    printf(WHITE"--------MENU--------\n"RESET);
    printf(MAGENTA"------- PUSH - 1 ---------\n");
    printf("--------- POP - 2 --------\n");
    printf("------ TOP ELEMENT - 3 ---\n");
    printf("-------- IS EMPTY - 4 ----\n");
    printf("--------- SIZE - 5 -------\n");
    printf("---- SEARCH IN STACK - 6 -\n");
    printf("--- REVERSE STACK - 7 ----\n");
    printf("--- MIN and MAX - 8 ------\n");
    printf("------ SORTING - 9 -------\n");
    printf("----- DISPLAY - 10 -------\n");
    printf("-------- EXIT - 0 --------\n"RESET);
}

bool parse_int(char*string, int*data){
    int i=0;
    int len = strlen(string);
    while(isspace(string[i])) i++;
    if(len == i ) return false;

    char integer_buffer[BUFFER_SIZE];
    int integer_chars = 0;

    if(string[i] == '-' || string[i] == '+'){
        integer_buffer[integer_chars] = string[i++];
        if(!isdigit(string[i])) return false;
    }
    // at least one digit should be present 
    if(!isdigit(string[i])) return false;
    //read digits 
    while (i<len && !isspace(string[i])){
        integer_buffer[integer_chars++] = string[i++];
    }
    integer_buffer[integer_chars] = '\0';
    while(isspace(string[i])) i++;
    if(string[i] != '\0') return false; 
    *data = atoi(integer_buffer);
    return true;
}

void Display(Stack*stack){
    if(stack==NULL){
        printf(RED"Stack is empty\n"RESET);
        return;
    }
    StackNode*temp=stack->top;
    printf(BLUE"Stack from Top to Bottom\n"RESET);
    printf("     ┌──────────────┐\n");
    while(temp!=NULL){
        printf("     |     %d      |   \n",temp->data);
        if (temp->next){
            printf("     ├──────▼─────┤\n");
        }
        temp=temp->next;
    }
    printf("     └──────────────┘\n\n");
}

StackNode*Node_Maker(int data){
    StackNode*newNode = (StackNode*)malloc(sizeof(StackNode));
    if(newNode==NULL){
        printf("List empty Error\n\n");
        exit(EXIT_FAILURE);
    }
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

void Clear(){
    int c;
    while((c = getchar())!= '\n' && c != EOF);
}

bool isEmpty(Stack*stack){
    return stack->top == NULL;
}

void push(Stack*stack, int data){
    StackNode*newNode = Node_Maker(data);
    newNode->next = stack->top;
    stack->top=newNode;
    stack->size++;
}

int pop(Stack*stack){
    if(isEmpty(stack)) return INT_MIN;
    StackNode*temp  = stack->top;
    int data  = temp->data;
    stack->top=temp->next;
    free(temp);
    stack->size--;
    return data;
}

bool topEl(Stack*stack, int* topElement){
    if (stack==NULL || stack->top ==NULL){
        printf(RED"Stack is empty\n\n"RESET);
        return false;
    }
    *topElement = stack->top->data;
    return true; 
}

