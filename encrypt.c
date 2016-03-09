#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "functions.c"



void myencrypt(int* key){
	char ch;
	FILE *fp;
	fp = fopen("alice.txt","r");
	if( fp == NULL )
   	{
    	perror("Error while opening the file.\n");
    	exit(EXIT_FAILURE);
	}

	int* str;
	str = (int *) malloc(4*sizeof(int));
	while( ( ch = fgetc(fp) ) != EOF ){
		str[0]=ch;

		if(( ch = fgetc(fp) ) != EOF)
		str[1]=ch;
		else{str[1]=0;}

		if(( ch = fgetc(fp) ) != EOF)
		str[2]=ch;
		else{str[2]=0;}

		if(( ch = fgetc(fp) ) != EOF)
		str[3]=ch;
		else{str[3]=0;}

		int i;

		//asscii to binary array
		int* t = get_block(str);

		int* perm = permutate(t,pseq1);
		for(i=0;i<16;i++){
			perm=subencrypt(perm,key ,sbox1);
		}
		int* ddperm = permutate(perm,pseq1);


		
		/*for(i=0;i<32;i++){
			printf("%d ",ddperm[i]);
		}
		printf("\n");*/


		int* numstrinng = get_numstr(ddperm);

		for(i=0;i<32;i++){
			printf("%d ",ddperm[i]);
		}
		printf("\n");

		for(i=0;i<4;i++){
			char cc=numstrinng[i];
			//printf("%c ",cc);
		}
		//printf("\n");


		
	}
}	


int main(){
	int key[32]={0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,0,1,1};

	int i;

	for(i=0;i<32;i++){
		printf("%d ",key[i]);
	}
	printf("\n");

	int* numstrinng = get_numstr(key);
	for(i=0;i<4;i++){
		printf("%d ",numstrinng[i]);
	}
	printf("\n");

	int* binstring = get_block(numstrinng);
	for(i=0;i<32;i++){
		printf("%d ",binstring[i]);
	}
	printf("\n");

	//myencrypt(key);
	
}




