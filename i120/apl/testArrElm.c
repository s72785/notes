#include<stdio.h>
int main(){
	char a[3][11]={
			"0123456789\0",
			"1234567890\0",
			"0987654321\0"
		};
	printf("%s\n",a[0]);
	return 0;
}
