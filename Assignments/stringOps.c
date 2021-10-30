#include <string.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

/*
Node* insertNodes(int value,Node*head){
    Node *ptr,*temp;
    temp=malloc(sizeof(Node));
    temp->data=value;
    temp->next=NULL;
    ptr=head;
    //ptr iterates through the linked list until next node is null
    while(ptr->next!=NULL){
        ptr = ptr->next;
    }
    ptr->next = temp;
    return head;
}*/

Node* insertNodes(int element,Node*head){
    Node *New = malloc(sizeof(Node));   
    New->data=element;      
    if(head==NULL) 
    {head = New;
        New->next= NULL;
        return head;
    }
    Node *cur=head;  
    Node *cur2=NULL;  
    while(cur!=NULL)  
    {    
        if (cur->data <= element)
        {cur2 = cur;
            cur = cur->next; 
        }
        else
        {if (cur2 == NULL)
            {New->next= head;
                head = New;
            }
            else
            {cur2->next = New;
                New->next= cur;
            }
            return head;
        }
    }
    cur2->next = New;
    New->next= NULL;
    return head;
}

Node* deleteNodes(int* count,int value,Node*head){
    //printf("going into if statement %d\n",head->data);
    if (head==NULL){
        return NULL;
    }
    Node*temp;
    Node*prev;
    prev=head;
    temp =head->next;
    //printf("going into if statement %d\n",temp->data);
    if (head->data==value){
      // printf("going into return condition %d\n",head->data);
        prev=head->next;
       // printf("delete %d when value =%d\n",temp->data,value);
        free(head);
        (*count)--;
       // printf("count=%d",count);
        return prev;
    }
    //printf("temp %p\n",temp);  
    while(temp!=NULL){
        //printf("temp %p\n",temp);  
        if (temp->data==value){
            prev->next= temp->next;
           //printf("delete %d when value =%d\n",temp->data,value);
            free(temp);
            (*count)--;
          //  printf("count=%d\n",*count);
            return head;
        }
        prev=temp;
        temp=temp->next;
        
    }
    return head;
}

void freeNodes(int count,Node*head){
    Node *ptr,*prev;
    ptr=head;
    prev=NULL;
    while(ptr!=NULL){
        prev=ptr;
        ptr=ptr->next;
        free(prev);
    }
}

/*
void freeNodes(int count,Node*head){
    Node *ptr,*prev;
    ptr=head->next;
    prev=head;
    while(ptr->next!=NULL){
        prev=ptr;
        ptr=head->next;
        free(prev);
    }
}

 void sortLinkedList(int count,Node*head){
    Node *noded=NULL, *temp = NULL;
    int tempvar;
    noded = head;
    temp = noded->next;
    while(noded!= NULL && noded->next != NULL){
        for(int j=0; j<count; j++){
            if(noded->data > temp->data){
                tempvar = noded->data;
                noded->data = temp->data;
                temp->data = tempvar;
            }
            temp=temp->next;
        }
        noded=noded->next;
      }
    }    
    //free(prev);
*/


// void swapNodes(Node *a, Node *b) { 
//     int temp = a->data; 
//     a->data = b->data; 
//     b->data = temp; 
// } 
// Node* sortNodes(Node*head){
//     Node *ordered,*ptr; 
//     ptr=head->next;
//     Node*prev=head;
//     Node*smallest=head;
//     Node*beforeSmallest=head;
//     int nums= head->data;
//     while (ptr!=NULL){
//         while(ptr->next!=NULL){
//         if (nums>ptr->data){
//             smallest=ptr;
//             nums=ptr->data;
//             beforeSmallest=prev;
//         }
//         prev=ptr;
//         ptr=ptr->next;
//         if (ordered==NULL){
//         ordered=smallest;   
//         }
//         else{
//        ordered->next=smallest;
//         }
//     }
//     prev=head;
//     smallest=head;
//     beforeSmallest=head;
//     ordered=ordered->next;
//     beforeSmallest->next= smallest->next;
//     }
// }
    // int i; 
    // int isTrue=0;
    // Node *ptr; 
    // Node *temp = NULL; 
    // if (head == NULL){
    //     return head; 
    // }
    // while (isTrue!=1){
    //     isTrue = 0; 
    //     ptr = head; 
    //     while (ptr->next != temp) { 
    //         if (ptr->data > ptr->next->data) {  
    //             swapNodes(ptr, ptr->next); 
    //             isTrue = 1; 
    //         } 
    //         ptr = ptr->next; 
    //     } 
    //     temp = ptr; 
    //    // printf("sorted %d",ptr->data);
    // }
    // return head;
//} 
// void printNodes (int count,Node*head){
//     printf("count in print function=%d\n",count);
//     Node *ptr=head->next;
//     printf("head in print function=%d\n",head->data);
//    // printf("head data %d",head->data);
//     //int t=head->data;
//     printf("head data ");
//     for(int i=1;i<count;i++){
//         //if (ptr->next->data!=t){
//         printf("%d\t",ptr->data);
//         ptr=ptr->next;
//        // t=ptr->data;    
//       //  }
//     }
// }
void printNodes(int count, Node*head){
    Node*ptr=head;
    printf("%d\n",count);
    while (ptr->next!=NULL){
        if(ptr->data!=ptr->next->data){
        printf("%d\t",ptr->data);
        }
        ptr=ptr->next;
    }
    printf("%d\t",ptr->data);
}
int main(int argc, char* argv[]){
    FILE* ptr;
    Node *head=NULL;
    ptr = fopen(argv[1],"r");
    char x;
    int num;
    int y=fscanf(ptr,"%c %d\n",&x,&num);
   // printf("y=%d",y);
    int count=0;
    //run through the file and add or delete nodes while keeping count
        while (y!=-1){
            if(x=='i'){
            //printf("%d", num);
                //to start a new LL
                if(head==NULL){
                head=malloc(sizeof(Node));
                head->data=num;
                head->next=NULL;
                }
               else{head=insertNodes(num,head);}
               //printf("num=%d\tchar=%c", num,x);
            count++;
            //printf("count=%d",count);
            }
            if(x=='d'){
          //printf("number=%d char=%c", num,x);
           head=deleteNodes(&count,num,head);
            //printf("modified &d", head->data);
            }
        y=fscanf(ptr,"%c %d\n",&x,&num);
        }
        fclose(ptr);
       // printNodes(count,head);
       //printf("count=%d",count);
       //sortLinkedList(count,head);
        printNodes(count,head);
       // printf("after sort");
       freeNodes(count,head);
