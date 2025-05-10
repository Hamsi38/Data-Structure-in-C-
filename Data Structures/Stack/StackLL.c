#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define BLUE "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define WHITE "\033[1;37m"
#define RED "\033[1:31m"
#define RESET "\033[0m"

#define BUFFER_SIZE 100
#define empty -1

typedef struct List
{
    int data;
    struct List*next;
}List;

// these are basic functions checking the value entered is integer or not
//Display of our stack and Menu bar
List*Create();
void Push(List**Node, int data);
int Pop(List**Node);
List*Node_Maker(int data);
void Clear();


void Menu();
bool parse_int(char*String, int *choice);
void Display(List*head);
void Integer_Checker();



int main(void){
    List*Top = Create();
    int choice, push_value;
    char buffer[BUFFER_SIZE];
    bool parse_condition, end_program;

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
                    Push(&Top,push_value);
                    break;
                case 2:
                    // printf("here is your Popped Value from Stack -->%d",);
                    break;
                case 10:
                    printf("Here is your Stack based on LinkedList\n");
                    Display(Top);
                    printf("----------------");
                    break;
                case 0:
                    printf(RED);
                    printf("Thx for using my program have a good day \n\n");
                    printf(RESET);
                    end_program = false;
                    break;
                default:
                    printf(RED);
                    printf("Please enter a number between 1 - 12 (include 1 and 12)\n and if you want to exit from program just enter 0\n\n ");
                    printf(RESET);
                    break;
                }
        }
        else{
            printf(RED);
            printf("---------------------------------\n");
            printf("INVALID INPUT PLEASE TRY AGAIN!!!\n");
            printf("---------------------------------\n\n");
            printf(RESET);
        }
    } while (end_program);
    return 0;
    }


void Menu(){
    printf(WHITE);
    printf("--------MENU--------\n");
    printf(RESET);
    printf(MAGENTA);
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
    printf(RESET);
}

List*Create(){
    return NULL;
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
    integer_buffer[i] = '\0';
    while(isspace(string[i])) i++;
    if(string[i] != '\0') return false; 
    *data = atoi(integer_buffer);
    return true;
}

//* this is the insert at begin in Linked list 
// this works for empty and non empty stack 
void Push(List**Node, int data){
    List*new = Node_Maker(data);
    new->next=*Node;
    *Node=new;
}

void Display(List*head){
    List*temp=head;
    if(temp==NULL){
        printf("Stack is empty\n\n");
        return;
    }
    printf("Stack from Top to Bottom\n");
    printf("┌───────────┐\n");
    while(temp!=NULL){
        printf("|    %d     |\n",temp->data);
        printf("_____________\n");
        temp=temp->next;
    }
    printf("|___________|\n\n");
}

List*Node_Maker(int data){
    List*newNode = (List*)malloc(sizeof(List));
    if(newNode==NULL){
        printf("List empty Error\n\n");
        exit(1);
    }
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

void Clear(){
    int c;
    while((c = getchar())!= '\n' && c != EOF);
}





