#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>



int* permutate(int* original, int permseq[]){
	int* duplicate = malloc(32*sizeof(int));
	int i;
	for(i=0;i<32;i++){
		duplicate[i]=original[permseq[i]];
	}
	return duplicate;
} 

int* depermutate(int* duplicate,int permseq[]){
	int* original= malloc(32*sizeof(int));
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

int* subencrypt(int* permkey,int* key ){

	



}










void myencrypt(int* key){
	char ch;
	FILE *fp;
	fp = fopen("alice.txt","r");
	if( fp == NULL )
   	{
    	perror("Error while opening the file.\n");
    	exit(EXIT_FAILURE);
	}
	int pseq1[32]= {17,6,18,16,4,21,15,25,20,30,14,5,31,7,1,23,26,19,28,27,0,8,29,24,22,2,13,9,11,12,3,10};
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

		//asscii to binary array
		int* t = get_block(str);
		int i;
		for(i=0;i<32;i++){
			printf("%d ",t[i]);
		}
		printf("\n");

		int* perm = permutate(t,pseq1);




	}
}	


int main(){

	char* key = malloc(4*sizeof(char));
	printf("Hey MAtey!! Enter ur 32-bit key ");
	scanf("%s", key);
	int* keynum = (int *) malloc(4*sizeof(int));
	keynum[0]=key[0];
	keynum[1]=key[1];
	keynum[2]=key[2];
	keynum[3]=key[3];
	int* keyarray = get_block(keynum);
	myencrypt(keyarray);
	
}




