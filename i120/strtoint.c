#include<stdio.h>
#include<math.h>
#include<stdlib.h>
/*
int strtoint(char *s, int l){
	int i,r;
	r=0;
	printf("\n\n", l, i, s);
	for(i=l; i>0; i--){
		printf("%d\t%d\t", l, i);
		r+=((int)(s[(l-i)])-48)*pow(10,i);
		printf("\t%d\t",(int)(s[(l-i)]));
		printf("\t%s\t",(char*)(48));
		printf("%d = %d * \n", r, pow(10,i));
	}
	return r;
}*/

int main(){
//	char *s1="test";
	char *s2="1234";
	
//	printf("%s\t=>\t%d\n", s1, strtoint(s1, 4));
	printf("%s\t=>\t%l\n", s2, strtol("1234"));
	return 0;
}
