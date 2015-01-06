#include <stdio.h>  //printf
#include <stdlib.h> //malloc, free, exit, atoi
#include <ctype.h>  //isdigit
#include <string.h> //(obsolete)? 
#include <assert.h> //assert()
#include "stack.h"  //custom "class" stack

// helper-function
int isnum(char *a) {
	if(*a == '\0') return 1;
	else return isdigit(*a) && isnum(a+1);
}

// Postfix-Rechner
int calc(char *expr[], int expr_length) {
	int k, n1, n2;
	stack *s = NULL;

	for(k = 0; k < expr_length; k++) {
		if(isnum(expr[k])) stack_push(&s, atoi(expr[k]));
		else { // Operator erwartet
			n2 = stack_pop(&s);
			n1 = stack_pop(&s);
			switch(expr[k][0]) {
				case '+': stack_push(&s, n1+n2); break;
				case '-': stack_push(&s, n1-n2); break;
				case '*': stack_push(&s, n1*n2); break;
				case '/': stack_push(&s, n1/n2); break;
				default: printf("Syntax error: %s unexpected\n", expr[k]); exit(EXIT_FAILURE);
			}
		}
	}
	n1 = stack_pop(&s);
	if(stack_isempty(&s)) return n1;
	else {
		printf("Missing operand\n");
		exit(EXIT_FAILURE);
	}
}


int main(int argc, char *argv[]) {
	printf("%d\n", calc(argv+1, argc-1));
	return 0;
}
