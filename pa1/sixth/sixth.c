#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
  char letter;
  int times;
  struct node* next;
}node;
//-------------------
node* newnode(char letter,int times){

struct node* newnode=(node*)malloc(sizeof(node));
newnode->letter=letter;
newnode->times=times;
newnode->next=NULL;

return newnode;
}
//-------------------------
int main(int argc,char** argv){

int l,i;

int n=strlen(argv[1]);
for( l=0;l<n;l++){
  if(argv[1][l]<'A'||argv[1][l]>'z'){
    printf("error\n");
    return 0;
  }
}
node* head=newnode('b',0);
node* point=head;

if(n==0){
  printf("error\n");
  return 0;
}
int numnode=1;
int count=0;
for(i=0;i<n;i++){
while(argv[1][i]==argv[1][i+1]){
  i++;
count++;
}
count++;
node* new=newnode(argv[1][i],count);
numnode++;
point->next=new;
point=point->next;
count=0;
}
int bl=0;//1:da1 0:buda
for(point=head->next;point!=NULL;point=point->next){
if(point->times!=1){
  bl=1;
}

}

if(bl==1){
  for(point=head->next;point!=NULL;point=point->next){
printf("%c%d",point->letter,point->times);
}
}else{
for(point=head->next;point!=NULL;point=point->next){
  printf("%c",point->letter);
}
}


printf("\n");
return 0;
}
