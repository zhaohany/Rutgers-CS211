#include<stdio.h>
#include<stdlib.h>

void printmatrix(int **matrix,int row);

int duplicate(int ** matrix,int row){

int i,j,k,l;
for( i=0;i<row;i++){
  for(j=0;j<row;j++){
    for( k=i+1;k<row;k++){
      for( l=0;l<row;l++){
        if(matrix[i][j]==matrix[k][l]){
          return 0;//duplicate
        }

      }
    }
  }
}
return 1;




}



//------------------
int sumrow(int ** matrix,int row,int n){
int j;
  int num=0;
    for( j=0;j<n;j++){
      num=num+matrix[row][j];
      }
    return num;
  }

int sumcol(int ** matrix,int col,int n){
	int j;
  int num=0;
  for( j=0;j<n;j++){
    num=num+matrix[j][col];
    }
  return num;
}

int sumdia1(int ** matrix,int n){
int num=0;
int i=0;
int j=0;
while(i!=n&&j!=n){
num=num+matrix[i][j];
i++;
j++;
}

return num;
}
int sumdia2(int ** matrix,int n){

  int num=0;
  int i=n-1;
  int j=n-1;
  while(i>=0&&j>=0){
  num=num+matrix[i][j];
  i--;
  j--;
  }

  return num;


}
//-------------------------------
int magic(int** matrix,int row){
int i;
int com=0;
int bas=sumrow(matrix,0,row);
//printf("bass is %d\n",bas);
int diag1=sumdia1(matrix,row);
//printf("diag1 is %d\n",diag1);
int diag2=sumdia2(matrix,row);
//printf("diag2 is %d\n",diag2);

//diag
if(diag1!=bas){
  return 0;
}
if(diag2!=bas){
  return 0;
}
//row---
for( i=0;i<row;i++){
com=sumrow(matrix,i,row);
//printf("sumrow is %d\n",com);
if(com!=bas){
  return 0;//not magic
}
}
//col-----
for(i=0;i<row;i++){
com=sumcol(matrix,i,row);
//printf("sumcol is %d\n",com);
if(com!=bas){
  return 0;//not magic
}
}

return 1;


}



//-----------------------
int main(int argc, char**argv){
  int d,i,j,k;
  FILE* fl;
  fl=fopen(argv[1],"r");

  if(fl==NULL){
    printf("error\n");
    return 0;
  }
  int row;
  fscanf(fl,"%d\n",&row);
  //creat matrix
    int** matrix=(int**)malloc(row*sizeof(int*));


  for( i=0;i<row;i++){
    matrix[i]=(int*)malloc(row*sizeof(int*));
  }

  //plug in data
  for( j=0;j<row;j++){
    for(k=0;k<row;k++){
      fscanf(fl,"%d\t",&d);
      matrix[j][k]=d;
    }
    fscanf(fl,"\n");
  }
//printmatrix(matrix,row);

int y=duplicate(matrix,row);
//printmatrix(matrix,row);
int x=magic(matrix,row);
//printf("y is %d\n",y);
//printf("x is %d\n",x);

if(x==1&&y==1){
  printf("magic\n");
  return 0;
}

printf("not-magic\n");



    return 0;



}

void printmatrix(int **matrix,int row){
	int j;
	int k;
  for(j=0;j<row;j++){
    for( k=0;k<row;k++){
  printf("%d\t",matrix[j][k]);
    }
    printf("\n");
  }
}
//---------------------
