#include<stdio.h>
#include<stdlib.h>

//---------------------------------------------
typedef struct node{
  int data;
  struct node* next;
}node;
//---------------------------------------------
node* newnode(int data,node* head){
  struct node* newnode=malloc(sizeof(node));
  newnode->data=data;
  newnode->next=head;
  return newnode;
}
//---------------------------------------------
node* checksame(node* head){
  struct node* pt1=head;
  struct node* pt2=head->next;
  struct node* prev=pt1;
  while(pt1!=NULL){
    pt2=pt1->next;
    prev=pt1;
    while(pt2!=NULL){
      if(pt1->data==pt2->data){
        prev->next=pt2->next;

      }
      prev=pt2;
      pt2=pt2->next;
    }
    pt1=pt1->next;
  }
  return head;
}
//---------------------------------------------
node* delete(int data,node*head){
  if(head==NULL){
    return head;
  }
  if(head->data==data){
    if(head->next==NULL){
      head=head->next;
      return head;
    }
    head=head->next;
  }
  struct node* point=head->next;
  struct node* prev=head;
  while(point!=NULL){
    if(point->data==data){
      prev->next=point->next;
    }
    prev=point;
    point=point->next;
  }
  return head;
}
//----------------------------------
int count(node* head){
  int count=0;
  if(head==NULL){
    return count;
  }
  struct node* point=head;
  while(point!=NULL){
    count++;
    point=point->next;
  }
  return count;

}
//-------------------------------------------
node* sort(node *head){
	struct node* point;
  struct node* small;
  struct node* stay;
  int temp;
  stay=head;

  while(stay!=NULL){
    point=stay->next;
    small=stay;
    while(point!=NULL){
      if(point->data<small->data){
        small=point;
      }
      point=point->next;
    }
    temp=stay->data;
    stay->data=small->data;
    small->data=temp;
    stay=stay->next;
  }
  return head;
}





//---------------------------------------------
int main(int argc, char** argv){

struct node* head=NULL;
struct node* point=NULL;


int num;
char op;
int countnum;


FILE *fl;
fl=fopen(argv[1],"r");

if(fl==NULL){
  printf("error\n");
  return 0;
}



while(fscanf(fl,"%c\t%d\n",&op,&num)!=EOF){


  if(op=='i'){
  head=newnode(num,head);
  head=checksame(head);


}else if(op=='d'){
  head=delete(num,head);

}
}



point=head;
countnum=count(point);

if(countnum==0){
  printf("%d\n",countnum);
  return(0);
}
printf("%d\n",countnum);


head=checksame(head);
head=sort(head);

point=head;


while(point!=NULL){
  printf("%d\t",point->data);
  point=point->next;
}


fclose(fl);
  return 0;
}
