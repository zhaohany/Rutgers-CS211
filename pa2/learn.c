#include "learn.h"

void print(double** matrix,int rownum,int comnum);
void printone(double* matrix,int rownum);
double** transpose(double**matrix,int row,int col);
double** inverse(double ** matrix,int row,int col);
double** toone(double** sample, int i, int j,int row,int col);
double** tozero(double** sample, int i, int j,int row,int col);
double** newtozero(double** sample, int i, int j,int row,int col);
double** times(double** matrix1, double** matrix2,int row1,int row2,int col1, int col2);
double** wcal(double** matrix,double ** Y,int row, int col);
double** sub(double** test, double** w,int row,int col);
void printdec(double** matrix,int row);

int main(int argc, char** argv){

	int attribnum,casenum,testnum;

	FILE* train;
	train=fopen(argv[1],"r");

	if(train==NULL){

		printf("cannot find training data file with that name\n");
		return 0;

	}

	FILE* test;
	test=fopen(argv[2],"r");


	if(test==NULL){

		printf("cannot find test data file with that name\n");
		return 0;

	}

	fscanf(train,"%d\n",&attribnum);
	fscanf(train,"%d\n",&casenum);
	fscanf(test,"%d\n",&testnum);

	/*printf("attribnum is %d,casenum is %d,testnum is %d \n",attribnum,casenum,testnum);*/
	int o,i,j;
	double** trainmatrix=(double**)malloc(casenum*sizeof(double*));
	for(i=0;i<casenum;i++){
		trainmatrix[i]=(double*)malloc((attribnum+1)*sizeof(double));
	}

	double** testmatrix=(double**)malloc(testnum*sizeof(double*));
	for(i=0;i<testnum;i++){
		testmatrix[i]=(double*)malloc((attribnum)*sizeof(double));
	}

	double** Y=(double**)malloc(casenum*sizeof(double*));
	for(i=0;i<casenum;i++){
		Y[i]=(double*)malloc(1*sizeof(double));
	}

	double** final=(double**)malloc((attribnum+1)*sizeof(double*));
	for(o=0;o<=attribnum;o++){
		final[o]=(double*)malloc(1*sizeof(double));
	}

	double** finalresult=(double**)malloc(testnum*sizeof(double*));
	for(o=0;o<testnum;o++){
		finalresult[o]=(double*)malloc(1*sizeof(double));
	}


	for(i=0;i<casenum;i++){
	for(j=1;j<=attribnum;j++){
		fscanf(train,"%lf%*[,]",&trainmatrix[i][j]);

	}
	fscanf(train,"%lf",&Y[i][0]);
	fscanf(train,"\n");
}
for(i=0;i<casenum;i++){
	trainmatrix[i][0]=1;
}
for(i=0;i<testnum;i++){
	for(j=0;j<attribnum;j++){
		fscanf(test,"%lf%*[,]",&testmatrix[i][j]);
	}
	fscanf(test,"\n");
}

final=wcal(trainmatrix,Y,casenum,attribnum+1);

finalresult=sub(testmatrix,final,testnum,attribnum);




free(trainmatrix);
free(testmatrix);
free(finalresult);
free(Y);
free(final);

/*print(trainmatrix,casenum,attribnum);
printf("\n");
printf("\n");
print(testmatrix,testnum,attribnum);
printf("\n");
printf("\n");
printone(Y,casenum);
printf("\n");
printf("\n");
trainmatrix=inverse(trainmatrix,casenum,attribnum);
print(trainmatrix,casenum,attribnum);
*/


	return 0;
}

//==================================================================================

double** sub(double** test, double** w,int row,int col){
	int o,p;
	double num=0;

	double** final=(double**)malloc(row*sizeof(double*));
	for(o=0;o<row;o++){
		final[o]=(double*)malloc(1*sizeof(double));
	}

	for(o=0;o<row;o++){
		num=w[0][0];
		for(p=0;p<col;p++){

			num=num+(test[o][p]*w[p+1][0]);
}
final[o][0]=num;
printf("%0.0lf\n", final[o][0]);
}

return final;
}

//==================================================================================
double** transpose(double**matrix,int row,int col){
double** result=(double**)malloc(col*sizeof(double*));
int i,j;
for(i=0;i<col;i++){
	result[i]=(double*)malloc(row*sizeof(double));
}

for(i=0;i<col;i++){
for(j=0;j<row;j++){
result[i][j]=matrix[j][i];

}


}

return result;
}
//==================================================================================
void printdec(double** matrix,int row){
	int i;
	for(i=0;i<row;i++){

		printf("%0.0lf\n",matrix[i][0]);

}


}
void print(double** matrix,int rownum,int comnum){
	int i,j;
	for(i=0;i<rownum;i++){
	for(j=0;j<comnum;j++){
		printf("%lf\t",matrix[i][j]);

}
	printf("\n");
}

}
void printone(double* matrix,int rownum){
	int i;
	for(i=0;i<rownum;i++){

		printf("%lf\t",matrix[i]);

}
	printf("\n");
}
//=================================================================================

double** inverse(double ** matrix,int row,int col){
double** result=(double**)malloc(row*sizeof(double*));
int i,j,k;
for(i=0;i<row;i++){
	result[i]=(double*)malloc((col*2)*sizeof(double));
}

for(i=0;i<row;i++){
	for(j=0;j<col;j++){
		result[i][j]=matrix[i][j];
	}
}
for(i=0;i<row;i++){
	for(j=col;j<(col*2);j++){
		if(j-col==i){
			result[i][j]=1;
		}else{
			result[i][j]=0;
		}

	}
}
//print(result,row,col*2);
//printf("\n");
for(i=0;i<row;i++){
	for(j=0;j<col;j++){
		if(i==j){//pivot
			result=toone(result,i,j,row,col*2);

			for(k=i+1;k<row;k++){
				result=tozero(result,k,j,row,col*2);
			}
		}
		}

	}
	//print(result,row,col*2);
	//printf("\n");

for(i=row-1;i>=0;i--){
	for(j=col-1;j>=0;j--){
		if(i!=j&&result[i][j]!=0){
			result=newtozero(result,i,j,row,col*2);
		}

	}
}
//print(result,row,col*2);
//printf("\n");
double** final=(double**)malloc(row*sizeof(double*));
for(i=0;i<row;i++){
	final[i]=(double*)malloc((col)*sizeof(double));
}
for(i=0;i<row;i++){
	for(j=0;j<col;j++){
		final[i][j]=result[i][j+col];
	}
}

return final;
}
//=================================================================================

double** toone(double** sample, int i, int j,int row,int col){

	double** matrix=(double**)malloc(row*sizeof(double*));
	int o,p;
	for(o=0;o<row;o++){
		matrix[o]=(double*)malloc((col)*sizeof(double));
	}

	for(o=0;o<row;o++){
		for(p=0;p<col;p++){
			matrix[o][p]=sample[o][p];
		}
	}

double fac;
int k,d;
	if(matrix[i][j]==1){
		return matrix;
	}else if(matrix[i][j]==0){
for(k=1;k<row;k++){
if(matrix[k][j]!=0){
	for(d=0;d<col;d++){
		matrix[i][d]=matrix[i][d]+matrix[k][d];
	}
return matrix;
}


}
printf("error");
return matrix;

	}else{
fac=matrix[i][j];
for(k=0;k<col;k++){

matrix[i][k]=matrix[i][k]/fac;

}

return matrix;
	}

printf("error");
return matrix;
}
//=================================================================================
double** tozero(double** sample, int i, int j,int row,int col){
	if(sample[i][j]==0){
		return sample;
	}
	double** matrix=(double**)malloc(row*sizeof(double*));
	int o,p;
	for(o=0;o<row;o++){
		matrix[o]=(double*)malloc((col)*sizeof(double));
	}

	for(o=0;o<row;o++){
		for(p=0;p<col;p++){
			matrix[o][p]=sample[o][p];
		}
	}

double fac=matrix[i][j];


	for(p=0;p<col;p++){
matrix[i][p]=matrix[i][p]/fac;

	}

int k;

	for(k=0;k<col;k++){
		matrix[i][k]=matrix[i][k]-matrix[j][k];
	}


return matrix;





}
//======================================================================================
double** newtozero(double** sample, int i, int j,int row,int col){
	if(sample[i][j]==0){
		return sample;
	}
	double** matrix=(double**)malloc(row*sizeof(double*));
	int o,p;
	for(o=0;o<row;o++){
		matrix[o]=(double*)malloc((col)*sizeof(double));
	}

	for(o=0;o<row;o++){
		for(p=0;p<col;p++){
			matrix[o][p]=sample[o][p];
		}
	}

double fac=matrix[i][j];

int k;

	for(k=0;k<col;k++){
		matrix[i][k]=matrix[i][k]-(matrix[j][k]*fac);
	}


return matrix;





}
//=======================================================================================

double** times(double** matrix1, double** matrix2,int row1,int row2,int col1, int col2){

	double** result=(double**)malloc(row1*sizeof(double*));
	int o,i,j,k;
	double num=0;
	for(o=0;o<row1;o++){
		result[o]=(double*)malloc((col2)*sizeof(double));
	}
	for(i=0; i<row1;i++){
		for(j=0; j<col2;j++){
			for(k=0; k<row2;k++){
				num=num+matrix1[i][k]*matrix2[k][j];

			}
			result[i][j]=num;

			num=0;

		}

	}

	return result;

}


//=======================================================================================

double** wcal(double** matrix,double ** Y,int row, int col){
	int o;

	double** xt=(double**)malloc(col*sizeof(double*));
	for(o=0;o<col;o++){
		xt[o]=(double*)malloc((row)*sizeof(double));
	}

	double** xinverse=(double**)malloc(col*sizeof(double*));
	for(o=0;o<col;o++){
		xinverse[o]=(double*)malloc((col)*sizeof(double));
	}

	double** xtx=(double**)malloc(col*sizeof(double*));
	for(o=0;o<col;o++){
		xtx[o]=(double*)malloc((col)*sizeof(double));
	}

	double** finalx=(double**)malloc(col*sizeof(double*));
	for(o=0;o<col;o++){
		finalx[o]=(double*)malloc(row*sizeof(double));
	}
	double** finaly=(double**)malloc(col*sizeof(double*));
	for(o=0;o<col;o++){
		finaly[o]=(double*)malloc(1*sizeof(double));
	}

xt=transpose(matrix,row,col);
//print(xt,col,row);
//printf("\n");

xtx=times(xt,matrix,col,row,row,col);
//print(xtx,col,col);
//printf("\n");


xinverse=inverse(xtx,col,col);
//print(xinverse,col,col);
//printf("\n");

finalx=times(xinverse,xt,col,col,col,row);
//print(xinverse,col,row);
//printf("\n");

finaly=times(finalx,Y,col,row,row,1);
//print(finaly,col,1);
//printf("\n");

return finaly;

}
