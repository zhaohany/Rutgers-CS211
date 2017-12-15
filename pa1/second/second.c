#include<stdio.h>
#include<stdlib.h>



int main(int argc,char**argv){

int num;

FILE* fl;
fl=fopen(argv[1],"r");

fscanf(fl,"%d\n",&num);

int arr[num];
int i;
for( i=0;i<num;i++){
  fscanf(fl,"%d\t",&arr[i]);
}
int temp;
int x;
int y;
for( x=0;x<num;x++){
for( y=x+1;y<num;y++){
if(arr[y]<arr[x]){
temp=arr[y];
arr[y]=arr[x];
arr[x]=temp;
}
}
}

int j;
for( j=0;j<num-1;j++){
  printf("%d\t",arr[j]);
}
printf("%d",arr[num-1]);
return 0;
}
