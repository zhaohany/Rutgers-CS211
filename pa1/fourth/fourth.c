#include<stdio.h>
#include<stdlib.h>

int** times(int** matrix,int** bass,int row){


int ** sum=(int**)malloc(row*sizeof(int*));
int i;
int j;
int k;
for(i=0;i<row;i++){
  sum[i]=(int*)malloc(row*sizeof(int*));
}


for( i=0; i<row; ++i){

  for( j=0; j<row; ++j){
      for( k=0; k<row; ++k){
          sum[i][j]+=matrix[i][k]*bass[k][j];
      }
}
}




for(i=0;i<row;i++){
  for( j=0;j<row;j++){
    matrix[i][j]=sum[i][j];

  }
}


return matrix;

}
//---------------------------------
void print(int** matrix,int row){
  int k;
  int i;
  int j;
for( i=0;i<row;i++){
  for(j=0;j<row;j++){
    k=matrix[i][j];
    if(j==row-1){
      printf("%d",k);
    }else{
      printf("%d\t",k);
    }


  }
  printf("\n");
}
}

int main(int argc,char**argv){
int i;
int d;
int j;
int k;
FILE* fl;
fl=fopen(argv[1],"r");

if(fl==NULL){
  printf("error\n");
}
int row;
fscanf(fl,"%d\n",&row);
//creat matrix
  int** matrix=(int**)malloc(row*sizeof(int*));
  int** result=(int**)malloc(row*sizeof(int*));

for(i=0;i<row;i++){
  matrix[i]=(int*)malloc(row*sizeof(int*));
}
for(i=0;i<row;i++){
  result[i]=(int*)malloc(row*sizeof(int*));
}
//plug in data
for( j=0;j<row;j++){
  for( k=0;k<row;k++){
    fscanf(fl,"%d\t",&d);
    matrix[j][k]=d;
  }
  fscanf(fl,"\n");
}
int n;
fscanf(fl,"%d",&n);

for( i=0;i<row;i++){
  for(j=0;j<row;j++){
    result[i][j]=matrix[i][j];

  }
}

for( i=1;i<n;i++){
result=times(result,matrix,row);

}
print(result,row);

  return 0;
}
