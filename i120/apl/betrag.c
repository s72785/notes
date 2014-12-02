#include<stdio.h>
double betrag(double betrag){
	if(betrag < 0){
		return (double)(-betrag);
	}else{
		return (double)betrag;
	}
}

int main(){
	printf("%10.2lf\n", betrag(-123.12));
	printf("%10.2lf\n", betrag(123123.12));
	return 0;
}
