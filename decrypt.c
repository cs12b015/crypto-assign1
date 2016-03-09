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
		for(i=0;i<4;i++){
			int cc = str[i];
			printf("%d ",cc);
		}
		printf("\n" );

		/*int* t = get_block(str);

		for(i=0;i<32;i++){
			printf("%d ",str[i] );
		}
		printf("\n" );*/
	}
}





int main(){
	int key[32]={0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,0,1,1};
	mydecrypt(key);
}