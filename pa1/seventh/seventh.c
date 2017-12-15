#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){

int num=0;
int i;
for( i=1;i<argc;i++){//argument count

num=strlen(argv[i]);


printf("%c", argv[i][num-1]);

}
printf("\n");
return 0;

}
