#include<stdio.h>
#include<stdlib.h>

int main(){
	char ch;
	FILE *fp;
	fp = fopen("alice.txt","r");
	if( fp == NULL )
   	{
    	perror("Error while opening the file.\n");
    	exit(EXIT_FAILURE);
	}

	
		char* str;
	while( ( ch = fgetc(fp) ) != EOF ){
		
		str = (char *) malloc(4);

		str[0]=ch;

		if(( ch = fgetc(fp) ) != EOF)
		str[1]=ch;

		if(( ch = fgetc(fp) ) != EOF)
		str[2]=ch;

		if(( ch = fgetc(fp) ) != EOF)
		str[3]=ch;

		printf("%s\n",str);

	}
	fclose(fp);
}
