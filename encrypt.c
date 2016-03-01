#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



int* permutate(int* original, int* permseq){
	int* duplicate;
	duplicate = (int *) malloc(32);
	int i;
	for(i=0;i<32;i++){
		duplicate[i]=original[permseq[i]];
	}
	return duplicate;
} 

int* depermutate(int* duplicate,int* permseq){
	int* original;
	original=(int *) malloc (32);
	int i;
	for(i=0;i<32;i++){
		original[permseq[i]]=duplicate[i];
	}
	return original;
}




int* get_block(int* str){
	
	int* ret = malloc(32*sizeof(int));
	int i,j;
	i=0;
	int c = str[i];
	for(i=0;i<4;i++){
		c = str[i];
		for(j=0;j<8;j++){
			ret[(i+1)*8-j] = c%2;
 			c = c/2;
		}
	}

	return ret;
}

int main(){
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

		//printf("%s\n",str);
		//int i;
		//for( i=0;i<4;i++)
       //  printf("%d ",str[i]);
       // printf("\n");
	}

	//fclose(fp);
	int i;
	int * t = get_block(str);
	for(i=0;i<32;i++){
		printf("%d",t[i]);
	}
}




