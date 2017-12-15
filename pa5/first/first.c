#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/******************************************Structure****************************************************/

typedef struct numst{
char name[80];
int valid;
struct numst* next;
}numst;


typedef struct gatest{
char name[80];
char input1[15];
char input2[15];
char output[15];
char multi[100];
struct gatest* next;
}gatest;

/******************************************Declare Methoad****************************************************/
numst* create(numst* temphead,char* name);
void travers(numst* temphead);
int convert(int dec);
int getnbit(int total,int n,int num);
void printma(int** matrix,int row,int col);
gatest* createg(gatest* temphead,char* name,char* input1,char* input2,char* output,char*multi);
void traversg(gatest* temphead);
void traversnum(numst* temphead);
int findint(char* name, numst* head);
int findout(char* name,int n, numst* head);
int notgate(int input);
int andgate(int input1,int input2);
int orgate(int input1,int input2);
int nandgate(int input1,int input2);
int norgate(int input1,int input2);
int xorgate(int input1,int input2);




/******************************************Main function****************************************************/


int main(int argc, char** argv){

/*declare varible*/
int input,output,result,dec,inc,num1,num2,num3,bl;
int i,j,k;
char* name=malloc(20*sizeof(char));
char* operation=malloc(20*sizeof(char));
char* name1=malloc(20*sizeof(char));
char* name2=malloc(20*sizeof(char));
char* name3=malloc(20*sizeof(char));
char* multi=malloc(100*sizeof(char));
numst* inthead=NULL;
numst* outhead=NULL;


/*read file*/
  FILE* fl;
  fl=fopen(argv[1],"r");
  if(fl==NULL){
    printf("wrong file name\n");
    return 0;
  }


/*read num of input and store in inthead LL*/
  fscanf(fl,"INPUTVAR %d",&input);
  //printf("input is %d\n",input);

  for(i=0;i<input;i++){
    fscanf(fl," %s",name);
    //printf("name is %s\n",name);
    inthead=create(inthead,name);
  }
fscanf(fl,"\n");


/*read num of output and store in inthead LL*/
  fscanf(fl,"OUTPUTVAR %d",&output);
  //printf("output is %d\n",output);

  for(i=0;i<output;i++){
    fscanf(fl," %s",name);
    //printf("name is %s\n",name);
    outhead=create(outhead,name);
  }

fscanf(fl,"\n");


/*calculate num of row*/
result=pow(2,input);
//printf("result is %d\n",result);

/*form grey code*/
int* greyint=malloc(result*sizeof(int));
greyint[0]=0;
greyint[1]=1;
greyint[2]=3;
greyint[3]=2;

for(i=2;i<input;i++){
inc=pow(2,i);
dec=inc-1;
while(dec>=0){
  greyint[inc]=greyint[dec]+pow(2,i);
  inc++;
  dec--;
}

}
//for(i=0;i<result;i++){
  //printf("%d\n",greyint[i]);
//}

int** matrix=malloc(result*sizeof(int*));
for(i=0;i<result;i++){
  matrix[i]=(int*)malloc((input+output)*sizeof(int));
}

for(i=0;i<result;i++){
  for(j=0;j<(input);j++){
    int temp;
temp=getnbit(input,j,greyint[i]);
matrix[i][j]=temp;
  }
}
//printma(matrix,result,(input+output));



/*read gate and store in gate LL*/
gatest* gate=NULL;

while(fscanf(fl,"%s",operation)==1){


  if(operation[0]=='N'&&operation[2]=='T'){

    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl,"\n");
gate=createg(gate,operation,name1,name2,name2,multi);
    //printf("NOT gate\n");
  }else if(operation[0]=='A'){
    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl," %s",name3);
    fscanf(fl,"\n");
    gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("AND gate\n");
  }else if(operation[0]=='O'){
    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl," %s",name3);
    fscanf(fl,"\n");
   gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("OR gate\n");
  }else if(operation[0]=='N'&&operation[3]=='D'){
    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl," %s",name3);
    fscanf(fl,"\n");
    gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("NAND gate\n");
  }else if(operation[0]=='N'&&operation[2]=='R'){
    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl," %s",name3);
    fscanf(fl,"\n");
    gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("NOR gate\n");
  }else if(operation[0]=='X'){
    fscanf(fl," %s",name1);
    fscanf(fl," %s",name2);
    fscanf(fl," %s",name3);
    fscanf(fl,"\n");
 gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("XOR gate\n");
  }else if(operation[0]=='D'){
  fscanf(fl,"%[^\n]", multi);
 
  gate=createg(gate,operation,name1,name2,name3,multi);
    //printf("DECODER gate\n");
  }else if(operation[0]=='M'){
	  
  fscanf(fl,"%[^\n]", multi);
 
  gate=createg(gate,operation,name1,name2,name3,multi);
  
    
    
    //printf("MULTIPLEXER gate\n");
  }
}

//traversg(gate);












numst* temphead=NULL;
//char* tempname=malloc(20*sizeof(char));



























for(i=0;i<result;i++){
	numst* pt=inthead;
	for(j=0;j<input;j++){
		pt->valid=matrix[i][j];
		pt=pt->next;
	}	
//traversnum(inthead);
	//travers(inthead);
	
gatest* move=gate;

while(move!=NULL){
 if(move->name[0]=='N'&&move->name[2]=='T'){
	 //printf("%s\n",move->input1);
    if(move->input1[0]>='A'&&move->input1[0]<='Z'){
		//printf("1\n");
     num1=findint(move->input1,inthead);
    // printf("num1(1):%d(%s)\n",num1,move->input1);
       //printf("num1:%d\n",num1);
     num2=notgate(num1);
     //printf("num2:%d\n",num2);
 }else{
	//printf("2\n");
	 num1=findint(move->input1,temphead);
     //printf("num1(1):%d(%s)\n",num1,move->input1);
       //printf("num1:%d\n",num1);
     num2=notgate(num1);
     //printf("num2:%d\n",num2);
	 
	 }
     
     if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num2,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num2,temphead);
	 if(bl==2){
		 temphead=create(temphead,move->output);
		 bl=findout(move->output,num2,temphead);
		 }
	 
	 
	 }
    num1=bl;

    //printf("NOT gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='A'){

 if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){
     num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
     
}else if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//input2 temp
	 num1=findint(move->input1,inthead);
     // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
    //  printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){//input1 temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
       //printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//both temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}
	
 if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num3,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num3,temphead);
	 if(bl==2){
	 temphead=create(temphead,move->output);
	 bl=findout(move->output,num3,temphead);
	 }
 }
    num1=bl;

    //printf("AND gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='O'){
   
 if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){
     num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=orgate(num1,num2);
     //printf("num2:%d\n",num2);
     
}else if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//input2 temp
	 num1=findint(move->input1,inthead);
     // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
    //  printf("num2:%d(%s)\n",num2,move->input2);
     num3=orgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){//input1 temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
       //printf("num2:%d(%s)\n",num2,move->input2);
     num3=orgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//both temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=orgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}
	
 if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num3,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num3,temphead);
	 if(bl==2){
	 temphead=create(temphead,move->output);
	 bl=findout(move->output,num3,temphead);
	 }
 }
    num1=bl;
    //printf("OR gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='N'&&move->name[3]=='D'){
    
 if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){
     num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=nandgate(num1,num2);
     //printf("num2:%d\n",num2);
     
}else if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//input2 temp
	 num1=findint(move->input1,inthead);
     // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
    //  printf("num2:%d(%s)\n",num2,move->input2);
     num3=nandgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){//input1 temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
       //printf("num2:%d(%s)\n",num2,move->input2);
     num3=nandgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//both temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=nandgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}
	
 if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num3,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num3,temphead);
	 if(bl==2){
	 temphead=create(temphead,move->output);
	 bl=findout(move->output,num3,temphead);
	 }
 }
    num1=bl;
    //printf("NAND gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='N'&&move->name[2]=='R'){
	 
 if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){
     num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=norgate(num1,num2);
     //printf("num2:%d\n",num2);
     
}else if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//input2 temp
	 num1=findint(move->input1,inthead);
     // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
    //  printf("num2:%d(%s)\n",num2,move->input2);
     num3=norgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){//input1 temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
       //printf("num2:%d(%s)\n",num2,move->input2);
     num3=norgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//both temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=norgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}
	
 if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num3,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num3,temphead);
	 if(bl==2){
	 temphead=create(temphead,move->output);
	 bl=findout(move->output,num3,temphead);
	 }
 }
    num1=bl;
    //printf("NOR gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='X'){
    
 if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){
     num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=xorgate(num1,num2);
     //printf("num2:%d\n",num2);
     
}else if(move->input1[0]>='A'&&move->input1[0]<='Z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//input2 temp
	 num1=findint(move->input1,inthead);
     // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
    //  printf("num2:%d(%s)\n",num2,move->input2);
     num3=xorgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='A'&&move->input2[0]<='Z'){//input1 temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
       //printf("num2:%d(%s)\n",num2,move->input2);
     num3=xorgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}else if(move->input1[0]>='a'&&move->input1[0]<='z'&&move->input2[0]>='a'&&move->input2[0]<='z'){//both temp
	 num1=findint(move->input1,temphead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,temphead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=xorgate(num1,num2);
     //printf("num2:%d\n",num2);
	
	}
	
 if(move->output[0]>='A'&&move->output[0]<='Z'){
		// printf("3\n");
		 
     bl=findout(move->output,num3,outhead);
 }else{
	 //printf("4\n");
	 bl=findout(move->output,num3,temphead);
	 if(bl==2){
	 temphead=create(temphead,move->output);
	 bl=findout(move->output,num3,temphead);
	 }
 }
    num1=bl;
    //printf("XOR gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='D'){
	  
	  
  num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
     bl=findout(move->output,num3,outhead);
    num1=bl;
    //printf("DECODER gate\n");
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
  }else if(move->name[0]=='M'){
	  
  num1=findint(move->input1,inthead);
      // printf("num1:%d(%s)\n",num1,move->input1);
        num2=findint(move->input2,inthead);
      // printf("num2:%d(%s)\n",num2,move->input2);
     num3=andgate(num1,num2);
     //printf("num2:%d\n",num2);
     bl=findout(move->output,num3,outhead);
    num1=bl;
    
    //printf("MULTIPLEXER gate\n");
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
	move=move->next;
}
	//traversg(gate);
	//traversnum(inthead);
	//traversnum(outhead);
	//traversnum(temphead);
	
	pt=outhead;
	for(k=input;k<(input+output);k++){
		matrix[i][k]=pt->valid;
		pt=pt->next;
		}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
	
	
	
	
	
	
	
	
	
	
	
	printma(matrix,result,(input+output));
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
return 0;
}


/******************************************add a new numst after****************************************************/
numst* create(numst* temphead,char* name){
  if(temphead==NULL){
    temphead=malloc(sizeof(numst));
    strcpy(temphead->name,name);
    temphead->next=NULL;
    return temphead;
  }
numst* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
numst* new=malloc(sizeof(numst));
strcpy(new->name,name);
new->next=NULL;
pt->next=new;
return temphead;

}

/******************************************print out the name of numst linked list****************************************************/
void travers(numst* temphead){
  numst* pt=temphead;
  while(pt!=NULL){
    printf("%s->",pt->name);
    pt=pt->next;
  }
  printf("\n");
  return;
}
/******************************************print out the number of numst linked list****************************************************/
void traversnum(numst* temphead){
  numst* pt=temphead;
  while(pt!=NULL){
    printf("%d->",pt->valid);
    pt=pt->next;
  }
    printf("\n");
  return;
}

/******************************************read a dec number and get the nst(from left) bit of that number****************************************************/
int getnbit(int total,int n,int num){

int s=total-n-1;
int b;
b=(num>>s)&1;
if(b==1){
  return 1;
}
if(b==0){
  return 0;
}

printf("error\n");
return 2;


}

/******************************************print out the whole matrix****************************************************/
void printma(int** matrix,int row,int col){

int i,j;
for(i=0;i<row;i++){
  for(j=0;j<col;j++){
    printf("%d ",matrix[i][j]);
  }
  printf("\n");
}

}

/******************************************Gate functions****************************************************/
int notgate(int input){
	//printf("notgate: %d",input);
  if(input==1){
    return 0;
  }
  if(input==0){
    return 1;
  }
  return 2;
}

int andgate(int input1,int input2){
	//printf("%d and %d\n",input1,input2);
  if(input1==1&&input2==1){
    return 1;
  }

  return 0;
}

int orgate(int input1,int input2){
  if(input1==1||input2==1){
    return 1;
  }

  return 0;
}

int nandgate(int input1,int input2){
  if(input1==0&&input2==0){
    return 1;
  }

  return 0;
}

int norgate(int input1,int input2){
  if(input1==1||input2==1){
    return 0;
  }

  return 1;
}

int xorgate(int input1,int input2){
	//printf("%d and %d\n",input1,input2);
  if(input1==1&&input2==0){
	 return 1;
	  }else if(input1==0&&input2==1){
		  
    return 1;
		  }else{

  return 0;
}
}

/******************************************add a gate linkedlist after****************************************************/
gatest* createg(gatest* temphead,char* name,char* input1,char* input2,char* output,char* multi){
  if(temphead==NULL){
    temphead=malloc(sizeof(gatest));
    strcpy(temphead->name,name);
    strcpy(temphead->input1,input1);
    strcpy(temphead->input2,input2);
    strcpy(temphead->output,output);
    strcpy(temphead->multi,multi);
    temphead->next=NULL;
    return temphead;
  }
gatest* pt=temphead;
  while(pt->next!=NULL){
    pt=pt->next;
  }
gatest* new=malloc(sizeof(gatest));
strcpy(new->name,name);
strcpy(new->input1,input1);
strcpy(new->input2,input2);
strcpy(new->output,output);
strcpy(new->multi,multi);
new->next=NULL;
pt->next=new;
return temphead;

}
/******************************************print out gate linked list****************************************************/
void traversg(gatest* temphead){
  gatest* pt=temphead;
  while(pt!=NULL){
    printf("%s(%s)(%s)(%s)(%s)->",pt->name,pt->input1,pt->input2,pt->output,pt->multi);
    pt=pt->next;
  }
    printf("\n");
  return;
}
/******************************************find the name in input linkedlist and return the valid****************************************************/
int findint(char* name, numst* head){
	
	numst* pt=head;
	//printf("%c(%c)->\n",pt->name[strlen(pt->name)-2],name[strlen(name)-2]);
	//printf("%c(%c)->\n",pt->name[strlen(pt->name)-1],name[strlen(name)-1]);
	while(pt!=NULL){
		if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){
			//printf("1here\n");
		if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){
			//printf("2here\n");
			//printf("valid: %d",pt->valid);
			return pt->valid;
			}
		}
		pt=pt->next;
		}
		return 2;
	
	
	};
/******************************************find the name in output linkedlist and return the bl(1:yes 2:not)****************************************************/
int findout(char* name,int n, numst* head){
	numst* pt=head;
	while(pt!=NULL){
		//printf("%c(%c)->",pt->name[strlen(pt->name)-2],name[strlen(pt->name)-2]);
		if(pt->name[strlen(pt->name)-1]==name[strlen(name)-1]){
		if(pt->name[strlen(pt->name)-2]==name[strlen(name)-2]){
			//printf("here");
			pt->valid=n;
			return 1;
			}
		
	
		}
			pt=pt->next;
	}
		return 2;
	
	
	};




































