int pseq1[32]= {0,6,18,26,4,21,15,25,8,30,14,5,31,7,1,23,16,19,28,27,17,20,29,22,24,2,13,9,11,12,3,10};

int sbox1[16]= {0,12,3,6,14,2,13,10,8,7,15,5,4,11,19,1};
int minibox1[8]={7,5,3,6,2,1,4,0};

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
			ret[(i+1)*8-j-1] = c%2;
 			c = c/2;
		}
	}
	return ret;
}



int* get_numstr(int* bin){
	int* ret = malloc(4* sizeof(int));
	int i,j,j2,k,temp,poww;
	for(i=0;i<4;i++){
		j = i*8;
		poww =128;
		temp=0;
		
		for(k=0;k<8;k++){
			temp +=bin[j+k]*poww;
			poww = poww/2;	
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
	int i,k,temp,ret,poww;
	temp =0;
	poww = 8;	
	for(k=0;k<4;k++){
		temp +=bi[k]*poww;
		poww = poww/2;	
	}
	ret = temp;	
	return ret;
}

int* getbin4(int num){
	int* ret = malloc(4*sizeof(int));
	int j;
	int c = num;
	for(j=0;j<4;j++){
		ret[4-j-1] = c%2;
 		c = c/2;
	}
	return ret;

}

int* substitute(int* xorres, int* sbox1){

	int i,j,tno,k;
	int* te4 = malloc(4*sizeof(int));
	int* ret = malloc(16*sizeof(int));
	int* te4a = malloc(4*sizeof(int));
	for(i =0;i<4;i++){
		j = 4*i;
		if(j%8==0){
			te4[0]= xorres[j+0];
			te4[1]= xorres[j+3];
			te4[2]= xorres[j+1];
			te4[3]= xorres[j+2];
			tno = getnum4(te4);
			te4a = getbin4(minibox1[tno]);
			ret[j+0]=te4a[0];
			ret[j+1]=te4a[1];
			ret[j+2]=te4a[2];
			ret[j+3]=te4a[3];
/*			printf("yesss %d\n",tno);
*/
		}
		else{
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
/*			printf("nooooope %d\n",tno);
*/		}

		

	}
		/*printf("\n");
		for(k=0;k<16;k++)
		{
			printf("%d ", ret[k]);
		}
		printf("\n");*/

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
	//int* substitute_temp = xorrightkey;
	int* secxor = xorarray(substitute_temp,left);
	for(i=0;i<16;i++){
		finalsub[i+16]=secxor[i];
	}

	return finalsub;

}


int* subdecrypt(int* perm,int* key, int* sbox1 ){

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
		finalsub[i+16]= perm[i]; // r i-e = l i
	}

	int* xorrightkey= xorarray(left,tempkey);
	int* substitute_temp = substitute(xorrightkey,sbox1);
	//int* substitute_temp = xorrightkey;
	int* secxor = xorarray(substitute_temp,right);
	for(i=0;i<16;i++){
		finalsub[i]=secxor[i];  // l 1 - 1 = right[i] + f(left[i],key)
	}

	return finalsub;
	

}