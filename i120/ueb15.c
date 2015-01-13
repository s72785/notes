#include <stdio.h>
#include <stdlib.h>

void file_error() {
	printf("Datei nicht lesbar\n");
	exit(1);
}

/* may do sth more/else soon */
int printfilecontent(char* filename){
	FILE* ifp;
	ifp = fopen(filename, "r");
	char c;

	if (ifp == NULL) file_error();
	while(fscanf(ifp, "%c", &c) != EOF) {
		printf("%c", c);
	}
	fclose(ifp);
	return 0;
}

char encaesar(char t, int c){
	return t = t + c % 128;
}

char decaesar(char t, int c){
	t = t - c + 128 % 128;
	if (t<10) t+=117;
	if (t>126) t-=c;
	return t;
}

int printfiledeciphered(char* filename, int cipher){
	FILE* ifp;
	ifp = fopen(filename, "r");
	char c;

	if (ifp == NULL) file_error();
	while(fscanf(ifp, "%c", &c) != EOF) {
		printf("%c", decaesar(c, cipher));
	}
	fclose(ifp);
	return 0;
}

int main() {
	int i;
	
	if(0 != printfilecontent("textfile.txt")){
		return 1;
	}
	
	//int chiffre=0;
	//printf("\n\nGeben Sie eine Chiffre an: ");
	//while(!(chiffre >= 10 && chiffre <= 126)){ scanf("%d", &chiffre); }
	
	//for(i=0; i<=126;i++){
		i=12;
		//printf("\n\n%d: ", i);
		if(0 != printfiledeciphered("bsp.txt", i)){
			return 1;
		}
	//}
	
//	char* text="Klardoch!";
//	for(i=0;i<9;i++)		printf("%c", text+i);
	
	return 0;
}
