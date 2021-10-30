#include<stdlib.h> 
   
typedef struct Node { 
    int data; 
    struct Node *left, *right; 
}Node;   
Node *newNode(int item) { 
    Node *temp =  (Node *)malloc(sizeof(Node)); 
    temp->data = item; 
    temp->left = temp->right = NULL; 
    return temp; 
} 
void ordered(Node *root) { 
  if (root != NULL) { 
        ordered(root->left); 
        printf("%d\t", root->data); 
        ordered(root->right); 
    } 
    free(root);
} 
Node* insert(Node* node, int key) { 
    if (node == NULL) return newNode(key); 
    if (key < node->data) 
        node->left  = insert(node->left, key); 
    else if (key > node->data) 
        node->right = insert(node->right, key);    
    return node; 
} 
int main(int argc, char* argv[]){
    FILE* ptr;
    Node *head=NULL;
    ptr = fopen(argv[1],"r");
    char x;
    int num;
    int y=fscanf(ptr,"%c %d\n",&x,&num);
    //printf("y=%d",y);
    int count=0;
        if(argc<2||ptr==NULL){
        printf("Error\n");
        }
        while (y!=-1){
            head=insert(head,num);
            y=fscanf(ptr,"%c %d\n",&x,&num);
        }
        ordered(head);
        fclose(ptr);
