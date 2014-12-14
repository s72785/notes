/* for kbhit, keypressed */

#ifndef	_MYIO_H
# define	_MYIO_H	1
#endif

#ifndef	_TERMIOS_H
# include <termios.h>
#endif
#ifndef	_UNISTD_H
# include <unistd.h>
#endif
#ifndef	_FCNTL_H
# include <fcntl.h>
#endif

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

char waitkbhit (void) {
	char c;

	while(!kbhit());

	c=getchar();

	return c;
}

void mypause( char *s ) {
	char c;

	printf( "%s", s );
	waitkbhit();
}

void cleartoendofline( void ) {
	char c;

	while( (c = getchar()) != '\n' && c != EOF );
}

/*
void myfflush {
		char c;
		//windows-alternative
		//fflush(stdin)
		while (getchar() != '\n');
}
*/

