#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int pseq1[32]= {17,6,18,16,4,21,15,25,20,30,14,5,31,7,1,23,26,19,28,27,0,8,29,24,22,2,13,9,11,12,3,10};

int sbox1[16]= {5,8,3,6,14,2,13,10,12,7,15,0,4,11,19,1};


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


int * get_numstr(int* bin){
	int* ret = malloc(4* sizeof(int));
	int i,j,k,temp;

	for(i=0;i<4;i++){
		j = i*8;
		temp =0;
		for(k=0;k<8;k++){
			temp +=bin[j+k];
			temp = temp*2;	
		}
		ret[i]= temp;	
	}
	return ret;
}

int xor(int x, int y){
	if(x==y)return 0;
	else return 1;	
}

int* xorarray(int* a,int* b){
	int* ret = malloc (16*sizeof(int));
	int i;
	for(i=0;i<16;i++){
		ret[i]=xor(a[i],b[i]);
	}
	return ret;
}


int getnum4(int* bi){
	int ret;
	int i,j,k,temp;
	temp =0;
	for(k=0;k<4;k++){
		temp +=bi[j+k];
		temp = temp*2;	
	}
	ret = temp;	
	return ret;
}

int* getbin4(int num){
	int* ret = malloc(4*sizeof(int));
	int j;
	int c = num;
	for(j=0;j<4;j++){
		ret[4-j] = c%2;
 		c = c/2;
	}
	return ret;

}

int* substitute(int* xorres, int* sbox1){

	int i,j,tno;
	int* te4 = malloc(4*sizeof(int));
	int* ret = malloc(16*sizeof(int));
	int* te4a = malloc(4*sizeof(int));
	for(i =0;i<4;i++){
		j = 4*i;
		te4[0]= xorres[j+0];
		te4[1]= xorres[j+3];
		te4[2]= xorres[j+1];
		te4[3]= xorres[j+2];
		tno = getnum4(te4);
		te4a = getbin4(sbox1[tno]);
		ret[j+0]=te4a[0];
		ret[j+1]=te4a[1];
		ret[j+2]=te4a[2];
		ret[j+3]=te4a[3];
	}
	return ret;
}



int* subencrypt(int* perm,int* key, int* sbox1 ){
	int* left = malloc(16*sizeof(int));
	int* right = malloc(16*sizeof(int));
	int* finalsub = malloc(32*sizeof(int));

	int* shufflekey = permutate(key,pseq1);
	int* tempkey = malloc(16*sizeof(int));
	
	int i;
	for(i=0;i<16;i++){
		left[i]=perm[i];
		right[i]=perm[i+16];
		tempkey[i]= shufflekey[i];
		finalsub[i]= perm[i+16];
	}
	int* xorrightkey= xorarray(right,tempkey);
	int* substitute_temp = substitute(xorrightkey,sbox1);
	int* secxor = xorarray(substitute_temp,left);
	for(i=0;i<16;i++){
		finalsub[i+16]=secxor[i];
	}

	return finalsub;

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
		/*int i;
		
		for(i=0;i<32;i++){
			
			printf("%d ",t[i]);
		}
		printf("\n");*/

		int * taa = substitute(t,sbox1);

		int i;
		
		for(i=0;i<32;i++){
			
			printf("%d ",taa[i]);
		}
		printf("\n");


		int* perm = permutate(t,pseq1);
		/*for(i=0;i<32;i++){

			printf("%d ",perm[i]);
		}
		printf("\n");
		printf("-------------------------------------------\n");*/
	}
}	


int main(){
	int key[32]={0,1,1,0,0,0,1,0,0,1,1,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,0,0,1,0,1,1};
	myencrypt(key);
	
}




