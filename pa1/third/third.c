#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int data;
  struct node* next;
}node;

typedef struct hashtable{
  int size;
  struct node** row;
}hashtable;

hashtable* newtable(int size){

  struct hashtable *maintable = (struct hashtable*) malloc(sizeof(struct hashtable));
  	maintable->size = size;
  	maintable->row = malloc(size*sizeof(struct node*));
	int i;
  	for (i = 0; i < size; i++) {
  		maintable->row[i] = NULL;
  	}
  	return maintable;


}
//----------------------------
int search(struct hashtable* maintable,int num){
  int key;
if(num<0){
key=(num*-1)%maintable->size;
}else{
key=num%maintable->size;
}
if(maintable->row[key]==NULL){
  return 0;//absent
}
if(maintable->row[key]->data==num){
  return 1;//present
}
struct node* point=maintable->row[key];

while(point->next!=NULL){
  if(point->next->data==num){
    return 1;//present
  }
  point=point->next;
}

return 0;//absent

}
//------------------------------
int insert(struct hashtable* maintable,struct node* new){

int data=new->data;
int key;
if(data<0){
  key=(data*-1)%maintable->size;
}else{

  key=data%maintable->size;
}

struct node* point;

if(maintable->row[key]==NULL){//no node in row
  maintable->row[key]=new;
  return 1;//added
}

if(maintable->row[key]->data==data){//first is data
  return 0;//duplicate
}
point=maintable->row[key];
while(point->next!=NULL){
if(point->next->data==data){
  return 0;//duplicate
}
point=point->next;
}

point->next=new;
return 1;//added


}


//-------------------------
node* newnode(int data,struct node* head){

  node* temp=(node*)malloc(sizeof(node));
  temp->data=data;
  temp->next=head;
  head=temp;


  return head;
}

//-------------------------------------
int main(int argc, char**argv){

//create hash table
struct hashtable* maintable=newtable(10000);


//open and read file
FILE* fl;

fl=fopen(argv[1],"r");
if(fl==NULL){
  printf("error\n");
  return 0;
}

int num;
char op;
int boolean1;
int boolean2;
struct node* temp=NULL;

while(fscanf(fl,"%c\t%d\n",&op,&num)!=EOF){
  if(op=='i'){
temp=NULL;
temp=newnode(num,temp);//creat node
boolean1=insert(maintable,temp);
if(boolean1==1){

  printf("inserted\n");

}if(boolean1==0){
  printf("duplicate\n");
}


  }
  if(op=='s'){
    boolean2=search(maintable,num);

    if(boolean2==1){
      printf("present\n");
    }
    if(boolean2==0){
      printf("absent\n");
    }
  }

}

return 0;

}
