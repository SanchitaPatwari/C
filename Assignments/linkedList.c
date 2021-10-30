#include <stdlib.h>
 
#define numberOfBuckets 10000
int SIZE = 10000;
int collision = 0;
int searches = 0;
typedef struct Node{
   int data;
   int key;
   struct Node *next;
}Node; 
typedef struct arr{
   Node *head;
   Node *tail;
}arr;
arr*array;
int find(Node *head, int value){
   int num = 0;
   Node *temp = head;
   while (temp != NULL){
       if(temp->data == value){
           return num;
       }
       temp = temp->next;
       num++;
   }
   return -1; 
}
int hash(int data){
   int key = data%10000;
   if(data<0){
    key= key+10000;
   }
  return key;
}
void inHash(){
   for( int i = 0; i < SIZE; i++){
      array[i].head = NULL;
      array[i].tail = NULL;
   }
};
void insert(int val){
   int index = hash(val);
   Node *head = (Node*) array[index].head;
   if(head == NULL){
   Node *new_Node = (Node*) malloc(sizeof(Node));
   new_Node->data = val;
   new_Node->key = index;
   new_Node->next = NULL;
   array[index].head = new_Node;
   array[index].tail = new_Node;
   }
   else{
       collision++;
       int locateIndex = find(head, val);
       if(locateIndex == -1) {
           Node *new_Node = (Node*) malloc(sizeof(Node));
           new_Node->data = val;
           new_Node->key = index;
           new_Node->next = NULL;
           array[index].tail->next = new_Node;
           array[index].tail = new_Node;
       }
   }
}
void search(int val){
   int index = hash(val);
   Node *list = (Node*) array[index].head;
   if(list == NULL){
       return;
   }
   int n = find(list, val);
   if(n == -1){
       return;
   }
   else{
       searches++;
   }
}
int main(int argc, char* argv[]){
   array = (arr*) malloc( SIZE * sizeof(arr));
   inHash();
   FILE* fp = fopen(argv[1] , "r");
   while(1){
      if(argv[1] == 0){
         break;
       }
     int val;
     char ch;
     int n = fscanf(fp, "%c\t%d\n", &ch, &val);
     if(n != 2){
       break;
   }
     if(ch == 'i'){
       insert(val);
     }
     else if(ch == 's') {
         search(val);
     }
}
printf("%d", collision);
printf("\n%d\n", searches);
for(int i = 0; i < SIZE; i++){
   Node* tmp;
   while(array[i].head != NULL){
       tmp = array[i].head;
       array[i].head = array[i].head->next;
       free(tmp);
   }
}
fclose(fp);
