/* for kbhit, keypressed */
#ifndef _MYIO_H
# define _MYIO_H

/* windows, can be implemented by somone who actually uses it */
// conio.h ? or sth more modern
/* linux */
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
int
kbhit (void) {
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

char
waitkbhit (void) {
	char c;

	while(!kbhit());

	c=getchar();

	return c;
}

char
waitnankbhit (void) {
	char c;

	while(c >= '0' && c <= '9' ){
		while(!kbhit());
		c=getchar();
	}

	return c;
}

char
waitnumkbhit (void) {
	char c='\0';

	while( !( c >= '0' && c <= '9' ) ){
		while(!kbhit());
		c=getchar();
	}

	return c;
}

char
waitfloatkbhit( int kpos, char delimiter ) {
	char c='\0';

	while( !( c >= '0' && c <= '9' ) && !(c == delimiter && kpos == 0) && c != '\n' ){
		while(!kbhit());
		c=getchar();
	}

	return c;
}

void
mypause( char *s ) {
	char c;

	printf( "%s", s );
	waitkbhit();
}

void
cleartoendofline( void ) {
	char c;

	while( (c = getchar()) != '\n' && c != EOF );
}

void
printcurrency(){
#ifdef WE
	puts(" " WE);
#endif
}

int
myinputint( int laenge, int output ) { /* output: 0=none, 1=digits, >char(output) */
	int i;
	int d=0;
	char c;

	for( i = 0; i < laenge; i++ ){
		c=waitnumkbhit();
		d += char2int(c) * (int)pow( 10, laenge-i-1 );
		if(DEBUG_PRINT == 2)printf("\n# %02d %d %d %d %04d %04d\t", c, c, i, laenge-i-1, (int)pow( 10, laenge-i-1 ), d);
		switch( output ){
			case 0:
			break;
			case 1: printf("%c", c);
			break;
			default: printf("%c", output);
		}
	}
	printf("\n");
	return d;
}

/*
void
* myfflush {
		char c;
		//windows-alternative
		//fflush(stdin)
		while (getchar() != '\n');
}
*/

#endif // _MYIO_H
