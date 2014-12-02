#include<math.h>
#include<stdio.h>	//u.a. f. prinf, scanf
#include<stdlib.h> //u.a. f. srand, time_t

int intZufallszahl(stellen){
	/* Intializes random number generator */
	time_t t;
	srand((unsigned) time(&t));
	int z=0;
	int i=0;
	while((pow(10,stellen-1)-z)>0){
		z = (int)rand() % (int)pow(10,stellen);
		i++;
	}
	printf("Zufallszahl brauchte %d Durchlaeufe!\n",i);
	return z;
}

int main(){
	printf("Zahl:\t%d\n", intZufallszahl(4));
	return 0;
}
