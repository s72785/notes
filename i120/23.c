#include<stdio.h>
#include<string.h>
#define MAX 20
    float sparbrief(float b, float a[], int s){
      int i;
      for(i=0; i<s; i++){
        b*=(1+a[i]);
      }
      return b;
    }
    float besterendite(float b, float z[],char banken[][20], int l, int c, float* max, char* bbank){
      int i,mac;
      float r[3];
      float br=0.0;
      for(i=0; i<l; i++){
        r[i]=sparbrief(b, &z[i], c);
        if(r[i] > br){
          max = &r[i];
          mac = i;
        }
      }
      printf("%i\n", i);
      strcpy(bbank, banken[mac]);//, ( strlen(banken[i]) > (MAX-1) ) ? (MAX-1) : strlen(banken[i]) );
      return *max;
    }
    int main(void){
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
      int s=4;
      int h=3;
      int i=0;
      float v=100.0;
      float br=0.0;
      char bestebank[MAX];

      //float b, float z, int l, int c,      
      for(i=0; i<h; i++){
        r[i]=sparbrief(v, a[i], s);
        printf("%d. Anlage-Betrag bei %s %8.2f ist nach %d Perioden %8.2f\n", (i+1), c[i], v, s, r[i]);
      }
      besterendite(v, *a, c, h, s, &br, bestebank);
      printf("bei %s\n", bestebank); 
      return 0;
    }
