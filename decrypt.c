#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "functions.c"


void mydecrypt(int* key){
	char ch;
	FILE *fp;
	fp = fopen("cipher.txt","r");
	if( fp == NULL )
   	{
    	perror("Error while opening the file.\n");
    	exit(EXIT_FAILURE);
	}

	int* str;
	str = (int *) malloc(4*sizeof(int));
	while( ( ch = fgetc(fp) ) != EOF ){
		str[0]=ch;
		if(str[0]<0){
			str[0]=str[0]+256;
		}

		if(( ch = fgetc(fp) ) != EOF){
			str[1]=ch;
			if(str[1]<0){
				str[1]=str[1]+256;
			}
		}
		else{str[1]=0;}

		if(( ch = fgetc(fp) ) != EOF){
			str[2]=ch;

			if(str[2]<0){
				str[2]=str[2]+256;
			}
		}
		else{str[2]=0;}

		if(( ch = fgetc(fp) ) != EOF){
			str[3]=ch;
			if(str[3]<0){
				str[3]=str[3]+256;
			}
		}
		else{str[3]=0;}
		int i;

		/*printf("numbSTRING\n");
		for(i=0;i<4;i++){
			printf("%d ",str[i]);
		}
		printf("\n");
		printf("\n");*/



		int* t = get_block(str);

	/*	printf("afters sbox\n");
		for(i=0;i<32;i++){
			printf("%d ",t[i]);
		}
		printf("\n");
		printf("\n");*/


		
		int* deperm1 = depermutate(t,pseq1);
		for(i=0;i<16;i++){
			deperm1=subdecrypt(deperm1,key ,sbox1);
		}

		int* deperm2 = depermutate(deperm1,pseq1);


		/*printf("binarray\n");
		for(i=0;i<32;i++){
			printf("%d ",deperm2[i] );
		}
		printf("\n" );
		printf("\n" );
*/

		int* numstrinng = get_numstr(deperm2);
/*
		printf("numstring\n");
		for(i=0;i<4;i++){
			printf("%d ",numstrinng[i]);
		}
		printf("\n");
		printf("\n");*/


		for(i=0;i<4;i++){
			char cc=numstrinng[i];
			printf("%c",cc);
		}
	}
}





int main(){
	int key[32]={0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,1};
	mydecrypt(key);
}