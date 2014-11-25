#include<stdio.h>
#include<string.h>
#define MAX 20
#define DEBUG 0

	float sparbrief(float betrag, float zinsen[], int perioden){

		int i;
		//float anfang=betrag;

		for(i=0; i < perioden; i++){
			betrag *= (1+zinsen[i]);

			if(DEBUG)printf("debug:\t%f   ", betrag);

		}

		if(DEBUG)printf("\n");

		return betrag;//-anfang;
    }

    float maxrendite(float betrag, float zinsen[][4],char banknamen[][20], int banken, int perioden, float *max, char *bestbank){

		int i;
		int mac = 0;
		float rendite[3]={0.0,0.0,0.0};

		for(i=0; i < banken; i++){
			rendite[i] = sparbrief(betrag, zinsen[i], perioden) - betrag;

			if(DEBUG)printf("debug:\ti:%i i[r_max]:%i r[i]%f r_max:%f\n", i, mac, rendite[i], *max);

			if(rendite[i] > *max){
				max = &rendite[i];
				mac = i;
			}

		}

		strcpy(bestbank, banknamen[mac]);//, ( strlen(banken[i]) > (MAX-1) ) ? (MAX-1) : strlen(banken[i]) );

		return *max;
    }

    int main(void){

		int s=4;
		int h=3;
		int i=0;
		float betrag=100.0;
		float besterendite = 0.0;
		char bestebank[MAX];

		//Banken
		char c[3][MAX];
		strcpy(c[0],"Bank1");
		strcpy(c[1],"Bank2");
		strcpy(c[2],"Bank3");

		//Zinsen
		float a[3][4]={
			{0.2, 0.3, 0.5, 0.6},
			{0.3, 0.4, 0.5, 0.5},
			{0.1, 0.2, 0.5, 0.7}
		};

		float r[3]={0.0,0.0,0.0};

		//float b, float z, int l, int c,      
		for(i=0; i<h; i++){
			r[i]=sparbrief(betrag, a[i], s);
			printf("%d. Anlage-Betrag bei %s %8.2f ist nach %d Perioden %8.2f\n", (i+1), c[i], betrag, s, r[i]);
		}

		besterendite=maxrendite( betrag, a, c, h, s, &besterendite, bestebank);
		printf("\nBestes Ergebnis bei %s: %8.2f\n", bestebank, besterendite); 

		return 0;
    }
