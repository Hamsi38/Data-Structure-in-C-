#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node{
    int data;
    struct Node* next;
} Node;
// Node* head:
// - A single pointer to the head node of the linked list.
// - Use when you only need to READ or TRAVERSE the list.
// - Changes to head inside functions will NOT affect the original head.

// Node** head:
// - A pointer to the head pointer (i.e., address of the head).
// - Use when you want to MODIFY the actual head inside a function.
//   (e.g., inserting at beginning, deleting from head, or inserting in an empty list)
// - Allows the function to change the real head value used in main().

Node*Create(int data);
void Insert_End(Node**head,int data);
void Display(Node*head);
void Insert_Begin(Node**head,int data);
void Insert_Pos(Node**head,int data,int pos);
int Size(Node*head);
void Delete_Begin(Node**head);
void Delete_End(Node**head);
void Delete_Pos(Node**head,int pos);
bool Search(Node*head,int value);
void Update_Val(Node**head,int pos,int val);
void Reverse_List(Node**head);
void Bottom_Up_MergeSort(Node**head);
Node*mergeSortedList(Node*left,Node*right);
void Delete_List(Node**head);

int main(){
    
    Node*head=NULL;

    int choice;
    int nr1,nr2,nr31,nr32;
    int pos;
    bool condition=true;
    int search_nr,change_pos,change_val;
    bool search_con;

    do
    {
        printf("-------------------------MENU-------------\n");
        printf("************** Insert at Beginning - 1\n");
        printf("************** Insert at End - 2\n");
        printf("************** Insert at Specific Position - 3\n");
        printf("************** Delete from Beginning - 4 \n");
        printf("************** Delete from End - 5\n");
        printf("************** Delete from Specific Position - 6\n");
        printf("************** Search for a value - 7 \n");
        printf("************** Update Node's Value - 8\n");
        printf("************** Reverse The List - 9\n");
        printf("************** Sort the List - 10\n");
        printf("************** Free the Entire List - 11\n");
        printf("************** Size of List - 12\n");
        printf("************** Display - 13\n");
        printf("************** Exit ---- 0\n");
        printf("ENTER YOUR ANSWER HERE ---> ");
        scanf("%d",&choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            printf("Value you want to Enter Begging of List---> ");
            scanf("%d",&nr1);
            Insert_Begin(&head,nr1);
            printf("\n");
            break;
        case 2:
            printf("Enter The Value End of List---> ");
            scanf("%d",&nr2);
            Insert_End(&head,nr2);
            break;
        case 3:
            printf("the Value --> ");
            scanf("%d",&nr31);
            printf("Position--> ");
            scanf("%d",&nr32);
            Insert_Pos(&head,nr31,nr32);
            break;
        case 4:
            printf("Before Deleting the First Element of List ");
            Display(head);
            printf("\n");
            printf("After ");
            Delete_Begin(&head);
            Display(head);
            break;
        case 5:
            printf("Before Deleting Last Element ");
            Display(head);
            printf("\n");
            Delete_End(&head);
            printf("After Deleting ");
            Display(head);
        case 6:
            printf("Enter the Position You want to free!!\n");
            scanf("%d",&pos);
            printf("Before Delete Element you want ");
            Display(head);
            printf("\n");
            Delete_Pos(&head,pos);
            printf("After\n");
            Display(head);
            break;
        case 7:
            printf("Enter The Number you want to search in List ");
            scanf("%d",&search_nr);
            search_con=Search(head,search_nr);
            if (search_con==true)
            {
                printf("Yes it is in the List\n");
            }
            else
            {
                printf("Sorry the Element you searched is not in List\n");
            }
            break;
        case 8:
            printf("Enter Position to change the value ");
            scanf("%d",&change_pos);
            printf("\n");
            printf("Enter the Value -->> ");
            scanf("%d",&change_val);
            Update_Val(&head,change_pos,change_val);
            printf("\n");
            printf("Your Updated List ");
            Display(head);
            break;
        case 9:
            printf("Your List Before Reversed ");
            Display(head);
            printf("\n");
            Reverse_List(&head);
            printf("After Reversed ");
            Display(head);
            break;
        case 10:
            printf("Your List Before Sorted ");
            Display(head);
            printf("\n");
            Bottom_Up_MergeSort(&head);
            printf("After Sorted ");
            Display(head);
            break;
        case 11:
            Delete_List(&head);
            break;
        case 12:
            printf("Size of List %d\n",Size(head));
            break;
        case 13:
            printf("HERE IS YOUR LIST \n");
            Display(head);
            break;
        case 0:
            printf("THANK YOU FOR USING MY PROGRAM!!!!! \n");
            condition=false;
            break;
        default:
            printf("Please enter a valid Number\n");
            break;
        }
        
    } while(condition);
    return 0;
}

Node*Create(int data){
    Node*newNode=(Node*)malloc(sizeof(Node));
    if (newNode==NULL)
    {
        printf("NULL Node!!!\n");
        exit(1);
    }
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

void Insert_End(Node**head,int data){
    Node*new=Create(data);
    if (*head==NULL)
    {
        *head=new;
        return;
    }
    Node*temp=*head;
    while (temp->next!=NULL)
    {
        temp=temp->next;
    }
    temp->next=new;   
}

void Display(Node*head){
    Node*temp=head;
    while (temp!=NULL)
    {
        printf("%d",temp->data);
        if (temp->next!=NULL)
        {
            printf("->");
        }
        temp=temp->next;
    }
    printf("\n");
}

void Insert_Begin(Node**head,int data){
    Node*new=Create(data);    
    new->next=*head;
    *head=new;
}

void Insert_Pos(Node**head,int data,int pos){
    if (pos>Size(*head))
    {
        printf("the Position You entered is out of Range!!!\n");
    }
    Node*new=Create(data);
    Node*temp=*head;
    Node*ptr;
    int i=1;
    while (i<pos-1)
    {
        temp = temp->next;
        ++i;
    }
        ptr=temp->next;
        temp->next=new;
        new->next=ptr;
}
/*	•	When you’re just reading or traversing the list (like counting size),
you don’t need to modify head.
	•	So passing Node* head (a single pointer) is enough. */
int Size(Node*head){
    int cnt=0;
    while (head!=NULL)
    {
        head=head->next;
        cnt++;
    }
    return cnt;
}

void Delete_Begin(Node**head){
    if(*head==NULL){
        printf("List is Empty!!!!\n");
        return;
    }
    Node*temp=(*head);//* if it is double pointer put it in parentheses 
    (*head)=temp->next;
    free(temp);
    temp = NULL;
}

void Delete_End(Node**head){
    Node*temp=*head;
    if (temp==NULL)
    {
        printf("LIST IS EMPTY\n");
        return;
    }
    else if (temp->next==NULL)
    {
        free(temp);
        *head=NULL;
    }
    while (temp->next->next!=NULL)  
    {
        temp=temp->next;
    }
    free(temp->next);
    temp->next=NULL;
}

void Delete_Pos(Node**head, int pos){
    Node*temp=*head;
    Node*ptr,*prev=NULL;
    int size=Size(*head);
    if (pos>size)
    {
        printf("The Position you entered out of range\n");
        return;
    }
    if (*head==NULL){
        printf("List is  empty \n");
        return;
    }
    else if (pos==1){
        Delete_Begin(head);
    }
    else if (pos==size){
        Delete_End(head);
    }
    for (int i = 0; i < pos-1; i++){
        prev=temp;
        temp=temp->next;
    }
    if (temp!=NULL)
    {
        prev->next=temp->next;
        free(temp);
    }
    else{
        printf("Data not present\n");
    }
}

bool Search(Node*head,int value){
    Node*temp=head;
    while (temp!=NULL)
    {
        if (temp->data==value)
        {
            return true;
        }
        temp=temp->next;
    }
    return false;
}

void Update_Val(Node**head,int pos,int val){
    Node*temp=*head;
    int size =Size(*head);
    if (*head==NULL)
    {
        printf("List is Empty\n");
        return;
    }
    if (pos>size)
    {
        printf("the Position Entered You is out of range!!\n");
        return;
    }
    if (pos<1)
    {
        printf("Enter a valid position please!!\n");
        return;
    }
    for (int i = 0; i < pos-1; i++)
    {
        temp=temp->next;
    }
    temp->data=val;
}

void Reverse_List(Node**head){
    Node*temp=*head;
    Node*prev=NULL;
    Node*next1;
    if (temp==NULL||temp->next==NULL)
    {
        printf("List is empty or just 1 element in list\n");
        return;
    }
    while (temp!=NULL)
    {
        next1=temp->next;
        temp->next=prev;
        prev=temp;
        temp=next1;
    }
    *head=prev;
}

void Bottom_Up_MergeSort(Node**head){
    //Base case: if the list is empty or has only one node , it's already sorted
    if (*head==NULL|| (*head)->next==NULL)
    {
        return;
    }
    int listSize=Size(*head);// get the total number of nodes in the list 
    Node*current = *head;
    //create a dummy node to act as the new head for sorted sublists
    Node*dummy=(Node*)malloc(sizeof(Node));
    dummy->next=*head;
    //iteratively merge sublists of increasing sizes(1,2,4,8,....) 
    for (int blockSize = 1; blockSize < listSize; blockSize *=2 )
    {
        Node*prev=dummy;
        current=dummy->next;

        while (current!=NULL)
        {
            Node*left=current;
            Node*right;
            //Move current to the end of the left sublist(blocksize nodes ahead)
            for (int i = 1; i < blockSize && current->next!=NULL; i++)
            {
                current=current->next;
            }
            //split the list: right stars after left
            right=current->next;
            current->next=NULL;//terminate the left list
            current=right;// move to the right sublist

            //move current to the end of the right sublist 
            for (int i = 1; i < blockSize&& current!=NULL && current->next!=NULL; i++)
            {
                current=current->next;
            }
            //split again if there is another sublist
            if (current!=NULL)
            {
                Node*temp1=current->next;
                current->next=NULL;//terminate right sublist
                current=temp1;// move to the next part
            }
            //merge two sorted sublists left and right
            prev->next=mergeSortedList(left,right);
            //move prec pointer to the last node of merges sublists 
            while (prev->next!=NULL)
            {
                prev=prev->next;
            }
        }
    }
    *head=dummy->next;//update head to the sorted list
    free(dummy);//ree the dummy node to prevent memory leak 
}


Node*mergeSortedList(Node*left,Node*right){
    if (left==NULL)
    {
        return right;
    }
    if(right==NULL){
        return left;
    }
    Node*result=NULL;
    // Compare the first elements of both lists and choose the smaller one
    if(left->data<=right->data){
        result=left;
        result->next=mergeSortedList(left->next,right);
    }
    else
    {
        result=right;
        result->next=mergeSortedList(left,right->next);
    }
    return result;
}

void Delete_List(Node**head){
    Node*temp;
    while (temp!=NULL)
    {
        temp=(*head)->next;
        free(*head);
        (*head)=temp;
    }
}
