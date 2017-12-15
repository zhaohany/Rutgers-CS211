#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/**************************Declare globle varible**********************/
int miss;
int hit;
int mr;
struct line** cache;
unsigned long int count;
int mw;
/**************************Create structure**********************/
typedef struct line{

unsigned long int tag;
int valid;
unsigned long int time;

}line;

/**************************Declare funtion**********************/
void readsim(unsigned long int tagindex,unsigned long int setindex,int assoc);
line** createcache(int setnum,int assoc);
void writesim(unsigned long int tagindex,unsigned long int setindex,int assoc);
void empty(int setnum, int assoc);
void prefetchww(unsigned long int tagindex,unsigned long int setindex,int assoc);
void prefetchrr(unsigned long int tagindex,unsigned long int setindex,int assoc);
void prefetchr(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn);
void prefetchw(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn);
void readsiml(unsigned long int tagindex,unsigned long int setindex,int assoc);
void writesiml(unsigned long int tagindex,unsigned long int setindex,int assoc);
void prefetchwwl(unsigned long int tagindex,unsigned long int setindex,int assoc);
void prefetchrrl(unsigned long int tagindex,unsigned long int setindex,int assoc);
void prefetchrl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn);
void prefetchwl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn);
/**************************Main funtion**********************/
int main(int argc, char** argv){
/*argv[1] is cachesize
  argv[2] is associativity
  argv[3] is cachepolicy
  argv[4] is blocksize
  argv[5] is tracefile
  dirmap: ass: 1
  fullassoc: 1 set */

  int cachesize=atoi(argv[1]);
  int blocksize=atoi(argv[4]);
  int n;//set assoc;
  int setnum;
  int assoc;

  int b;
  int s;
  //int t;




  char work;
  unsigned long int address;
  unsigned long int newaddress;
  unsigned long int setmask;
  //unsigned long int tagmask;
  unsigned long int tagindex;
  unsigned long int setindex;
  unsigned long int tagindexn;
  unsigned long int setindexn;
  //unsigned long int blockmask;

if(argv[3][0]=='f'){

  FILE* fl;
  fl=fopen(argv[5],"r");

  if(fl==NULL){

    printf("cannot find tracefile with that name\n");
    return 0;

  }

//printf("70: here\n");

/**************************calculate assoc and setnum in different map form(dir,full,set asso)**********************/
if(argv[2][0]=='d'){//direct map

assoc=1;
setnum=cachesize/blocksize;

}else if(argv[2][5]!=':'){//fullassoc
setnum=1;
assoc=cachesize/blocksize;
}else{//n way associat chache

    sscanf(argv[2],"assoc:%d",&n);
    assoc=n;
    setnum=cachesize/blocksize/n;

  }



/**************************calculate how many bit in each index and mask**********************/
b=log(blocksize)/log(2);
s=log(setnum)/log(2);

//blockmask=blocksize-1;
setmask=((1<<s)-1);

//t=48 - (b + s);


/**************************update cache based on num**********************/
cache=createcache(setnum,assoc);




//printf("110: here\n");


/**************************loop begin(read file)without pre**********************/
while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){




/**************************calculate the index**********************/
/*setmask=((1<<s)-1)&(address>>b);

tagmask=address>>(s+b);




setindex=(address&setmask)>>b;
tagindex=((address&tagmask)>>b)>>s;
*/



setindex=(address>>b)&setmask;
tagindex=address>>(b+s);

//printf("set: %lx   tag:%lx\n",setindex,tagindex);

/**************************different work-mode**********************/

if(work=='R'){
	
	readsim(tagindex,setindex,assoc);
	
	
	}else if(work=='W'){
		writesim(tagindex,setindex,assoc);
	}


}

fclose(fl);


  fl=fopen(argv[5],"r");

  if(fl==NULL){

    printf("cannot find tracefile with that name\n");
    return 0;

  }
/**************************print the cache**********************/
/*int i,j;
for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}*/
 printf("no-prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);

/**************************empty the cache**********************/
empty(setnum,assoc);


/*for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}

 printf("********************\nmiss is %d\nhit is %d\nmr is %d\nmw is %d\n******************************",miss,hit,mr,mw);
 
 */
 
/**************************loop begin(read file)with pre**********************/
while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){




/**************************calculate the index**********************/
/*setmask=((1<<s)-1)&(address>>b);

tagmask=address>>(s+b);




setindex=(address&setmask)>>b;
tagindex=((address&tagmask)>>b)>>s;
*/


/**************************The original address**********************/
setindex=(address>>b)&setmask;
tagindex=address>>(b+s);

newaddress=address+blocksize;
setindexn=(newaddress>>b)&setmask;
tagindexn=newaddress>>(b+s);

//printf("set: %lx   tag:%lx\n",setindex,tagindex);

/**************************different work-mode**********************/

if(work=='R'){
	
	prefetchr(tagindex,setindex,assoc,tagindexn,setindexn);
	
	
	}else if(work=='W'){
		prefetchw(tagindex,setindex,assoc,tagindexn,setindexn);
	}


}
/**************************print**********************/

/*for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}*/

 printf("with-prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
 
 
/**************************lru begin**********************/
}else if(argv[3][0]=='l'){
	
  FILE* fl;
  fl=fopen(argv[5],"r");

  if(fl==NULL){

    printf("cannot find tracefile with that name\n");
    return 0;

  }

//printf("70: here\n");

/**************************calculate assoc and setnum in different map form(dir,full,set asso)**********************/
if(argv[2][0]=='d'){//direct map

assoc=1;
setnum=cachesize/blocksize;

}else if(argv[2][5]!=':'){//fullassoc
setnum=1;
assoc=cachesize/blocksize;
}else{//n way associat chache

    sscanf(argv[2],"assoc:%d",&n);
    assoc=n;
    setnum=cachesize/blocksize/n;

  }



/**************************calculate how many bit in each index and mask**********************/
b=log(blocksize)/log(2);
s=log(setnum)/log(2);

//blockmask=blocksize-1;
setmask=((1<<s)-1);

//t=48 - (b + s);


/**************************update cache based on num**********************/
cache=createcache(setnum,assoc);




//printf("110: here\n");


/**************************loop begin(read file)without pre**********************/
while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){




/**************************calculate the index**********************/
/*setmask=((1<<s)-1)&(address>>b);

tagmask=address>>(s+b);




setindex=(address&setmask)>>b;
tagindex=((address&tagmask)>>b)>>s;
*/



setindex=(address>>b)&setmask;
tagindex=address>>(b+s);

//printf("set: %lx   tag:%lx\n",setindex,tagindex);

/**************************different work-mode**********************/

if(work=='R'){
	
	readsiml(tagindex,setindex,assoc);
	
	
	}else if(work=='W'){
		writesiml(tagindex,setindex,assoc);
	}


}

fclose(fl);


  fl=fopen(argv[5],"r");

  if(fl==NULL){

    printf("cannot find tracefile with that name\n");
    return 0;

  }
/**************************print the cache**********************/
/*int i,j;
for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}*/
 printf("no-prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);

/**************************empty the cache**********************/
empty(setnum,assoc);


/*for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}

 printf("********************\nmiss is %d\nhit is %d\nmr is %d\nmw is %d\n******************************",miss,hit,mr,mw);
 
 */
 
/**************************loop begin(read file)with pre**********************/
while(fscanf(fl, "%*x: %c %lx", &work, &address)==2){




/**************************calculate the index**********************/
/*setmask=((1<<s)-1)&(address>>b);

tagmask=address>>(s+b);




setindex=(address&setmask)>>b;
tagindex=((address&tagmask)>>b)>>s;
*/


/**************************The original address**********************/
setindex=(address>>b)&setmask;
tagindex=address>>(b+s);

newaddress=address+blocksize;
setindexn=(newaddress>>b)&setmask;
tagindexn=newaddress>>(b+s);

//printf("set: %lx   tag:%lx\n",setindex,tagindex);

/**************************different work-mode**********************/

if(work=='R'){
	
	prefetchrl(tagindex,setindex,assoc,tagindexn,setindexn);
	
	
	}else if(work=='W'){
		prefetchwl(tagindex,setindex,assoc,tagindexn,setindexn);
	}


}
/**************************print**********************/

/*for(i=0;i<setnum;i++){
  for(j=0;j<assoc;j++){
  printf("Valid:%d\t tag: %lx\n",cache[i][j].valid,cache[i][j].tag);
}
printf("--------------------------------\n\n");
}*/

 printf("with-prefetch\n");
 printf("Memory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n",mr,mw,hit,miss);
	
	
	
	
	
	}else{
		printf("policy not correct");
		}
return 0;
}

/**************************malloc cache funtion**********************/
line** createcache(int setnum,int assoc){
  int i,j;
  cache=(line**)malloc(setnum*sizeof(line*));
  for(i=0;i<setnum;i++){
    cache[i]=(line*)malloc((assoc)*sizeof(line));
  }

  for(i=0;i<setnum;i++){
    for(j=0;j<assoc;j++){
         cache[i][j].valid=0;

    }
  }
  
 


return cache;
}



///**************************read mode funtion**********************/
void readsim(unsigned long int tagindex,unsigned long int setindex,int assoc){

int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("210 problem");

return;

}
///**************************write mode funtion**********************/
void writesim(unsigned long int tagindex,unsigned long int setindex,int assoc){

int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	mw++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			mw++;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			mw++;
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("360 problem");

return;

}

void empty(int setnum, int assoc){
	int i,j;
	for(i=0;i<setnum;i++){
		for(j=0;j<assoc;j++){
			cache[i][j].tag=0;
			cache[i][j].valid=0;
			cache[i][j].time=0;

	}
	}
	miss=0;
	hit=0;
	mr=0;
	mw=0;
	count=0;
}

void prefetchww(unsigned long int tagindex,unsigned long int setindex,int assoc){
	
	int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	
	mr++;
	
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	
	
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			
			return;
		}
			
		if(i==(assoc-1)){
			
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("439 problem");

return;
	
	
	
	}
void prefetchrr(unsigned long int tagindex,unsigned long int setindex,int assoc){
	
	int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){

	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			
			return;
		}
			
		if(i==(assoc-1)){
			
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("499 problem");
	
	
	
	}
	
	
	
void prefetchw(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
	
int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	mw++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	prefetchww(tagindexn,setindexn,assoc);
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			mw++;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			mw++;
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        prefetchww(tagindexn, setindexn,assoc);
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("360 problem");

return;
	
	
	
	}
void prefetchr(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
	
	
int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	prefetchrr(tagindexn,setindexn,assoc);
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        prefetchrr(tagindexn,setindexn,assoc);
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("210 problem");

return;
	
	
	}


//=================================================

void readsiml(unsigned long int tagindex,unsigned long int setindex,int assoc){

int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			count++;
			cache[setindex][i].time=count;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("210 problem");

return;

}
///**************************write mode funtion**********************/
void writesiml(unsigned long int tagindex,unsigned long int setindex,int assoc){

int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	mw++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			mw++;
			count++;
			cache[setindex][i].time=count;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			mw++;
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("360 problem");

return;

}



void prefetchwwl(unsigned long int tagindex,unsigned long int setindex,int assoc){
	
	int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	
	mr++;
	
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	
	
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			
			return;
		}
			
		if(i==(assoc-1)){
			
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("439 problem");

return;
	
	
	
	}
void prefetchrrl(unsigned long int tagindex,unsigned long int setindex,int assoc){
	
	int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){

	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	
	
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			
			return;
		}
			
		if(i==(assoc-1)){
			
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("499 problem");
	
	
	
	}
	
	
	
void prefetchwl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
	
int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	mw++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	prefetchww(tagindexn,setindexn,assoc);
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			mw++;
			count++;
			cache[setindex][i].time=count;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			mw++;
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        prefetchww(tagindexn, setindexn,assoc);
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("360 problem");

return;
	
	
	
	}
void prefetchrl(unsigned long int tagindex,unsigned long int setindex,int assoc,unsigned long int tagindexn,unsigned long int setindexn){
	
	
int i,j,min;

for(i=0;i<assoc;i++){
	if(cache[setindex][i].valid==0){
	miss++;
	mr++;
	count++;
	cache[setindex][i].valid=1;
	cache[setindex][i].tag=tagindex;
	cache[setindex][i].time=count;
	
	prefetchrr(tagindexn,setindexn,assoc);
	return;
	}else{
		
		
		
		
		
		if(cache[setindex][i].tag==tagindex){
			hit++;
			count++;
			cache[setindex][i].time=count;
			return;
		}
			
		if(i==(assoc-1)){
			miss++;
			mr++;
			
			min=0;
			for(j=0;j<assoc;j++){
			
			if(cache[setindex][j].time<=cache[setindex][min].time){
				min=j;
			}	
			}
			
			
			cache[setindex][min].valid=1;
	        cache[setindex][min].tag=tagindex;
	        count++;
	        cache[setindex][min].time=count;
	        prefetchrr(tagindexn,setindexn,assoc);
	        return;
		}
		
		
		
		
		}
		
		
		}


printf("210 problem");

return;
	
	
	}
