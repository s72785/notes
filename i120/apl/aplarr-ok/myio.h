/* for kbhit, keypressed */
#ifndef _MYIO_H
#define _MYIO_H

#ifndef _STDIO_H
# include <stdio.h>
#endif

/* windows, can be implemented by somone who actually uses it */
// conio.h ? or sth more modern
/* linux */
# include <termios.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

int
kbhit (void) {
	struct termios oldt, newt;
	int ch=0;
	int oldf=0;

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
	char c='\0';

	while(!kbhit());

	c=getchar();

	return c;
}

char
waitnumkbhit( int enter, int backspace ) {
	char c='\0';

	while( !( c >= '0' && c <= '9' ) && !( enter == 1 && ( c == '\n' || c == '\r' ) ) && !( backspace == 1 && ( c == 8 ) ) ){
		while(!kbhit());
		c=getchar();
	}

	return c;
}

char
waitfloatkbhit( int kpos, char delimiter, int enter, int backspace ) {
	char c='\0';

	while( !( c >= '0' && c <= '9' ) && !(c == delimiter && kpos == 0) && !( enter == 1 && ( c == '\n' || c == '\r' ) ) && !( backspace == 1 && ( c == 8 ) ) ){
		while(!kbhit());
		c=getchar();
	}

	return c;
}

void
mypause( char *s ) {
	char c = '\0';

	printf( "%s", s );
	while( !( c == '\n' || c == '\r' ) ){
		while(!kbhit());
		c=getchar();
	}
}

void
cleartoendofline( void ) {
	char c='\0';

	while( (c = getchar()) != '\n' && c != EOF );
}

void
printcurrency() {
#ifdef WE
	puts(" " WE);
#endif
}

int
myinputint( int laenge, int output, int enter, int backspace ) { /* rc: 0=none, 1=digits, >char(output) */
	int i;
	int d=0;
	char c;

	for( i = 0; i < laenge; i++ ){
		c=waitnumkbhit( enter, backspace );
		d += ( ( isnumchar(c) )? char2int(c) * (int)pow( 10, laenge-i-1 ) : 0 );
		if( c == 8 ) d = d / 10;
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

int
askyesno(char* text){
	int a = 9;

	printf("%s", text);

	while(!( isboolint( a ) )) {
		a = char2int(waitnumkbhit(0, 0));
	}
	if(DEBUG_PRINT)printf( "\n# Antwort: %d %c \t", a, a );
	printf("%i\n", a);

	return a;
}

int
myeingabeganzzahl( int laenge, int type, int enter, int backspace, char* text ) {
	printf("%s", text);
		
	return myinputint( laenge, type, enter, backspace );
}

#endif // _MYIO_H
