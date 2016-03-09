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
	int* t;
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
<<<<<<< HEAD
		t = get_block(str);
		/*int i;
		
		for(i=0;i<32;i++){
			
			printf("%d ",t[i]);
=======
		int* t = get_block(str);

		int* perm = permutate(t,pseq1);
		for(i=0;i<16;i++){
			perm=subencrypt(perm,key ,sbox1);
>>>>>>> 670e03429e66d72f493b2ce9a1230a8ea3c3ff70
		}
		int* ddperm = permutate(perm,pseq1);

<<<<<<< HEAD
		


		int* perm = permutate(t,pseq1);
		/*for(i=0;i<32;i++){

			printf("%d ",perm[i]);
		}
		printf("\n");
		printf("-------------------------------------------\n");*/
=======

		
		/*for(i=0;i<32;i++){
			printf("%d ",ddperm[i]);
		}
		printf("\n");*/


		int* numstrinng = get_numstr(ddperm);


		char tem;
		for(i=0;i<4;i++){
			//tem=numstrinng[i];
			char cc=numstrinng[i];
			printf("%c",cc);
		}
		/*printf("\n");*/


		
>>>>>>> 670e03429e66d72f493b2ce9a1230a8ea3c3ff70
	}
	int * taa = substitute(t,sbox1);

	int i;
	
	for(i=0;i<32;i++){
		printf("%d ",t[i]);
	}
	printf("\n");

	for(i=0;i<32;i++){
		printf("%d ",taa[i]);
	}
	printf("\n");
}	


int main(){
	int key[32]={0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,0,1,1};
	myencrypt(key);
	
}




