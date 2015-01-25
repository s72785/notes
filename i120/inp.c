#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

/* http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html  */
int kbhit (void) {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
	ch = getchar();
 
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);
 
	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

char keypressed (void) {
	char c;

	while(!kbhit());

	c=getchar();

	return c;
}

//menue(char **punkte={"Punkt1","Punkt2"}, char *eingaben={'1','2'}, int l=2, int** )

int main (void) {
	char c = '\0';

	printf("Einfach eine Taste drücken!\n");
	c = keypressed();

	if (c != '\0') {
		printf("Du hast '%c' gedrueckt!\n", c);
		return 0;
	} else {
		return 1;
	}
}
