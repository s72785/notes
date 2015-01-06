#include <stdlib.h>
#include <assert.h>
#include "stack.h"

int stack_push(stack **this, int item){
	stack *first = (stack*) malloc(sizeof(stack)); //declare new first element and allocate memory sufficient for a stack element
	if(!first) {
		//printf("stack_push: out of memory\n");
		return 1;//abort();
	}
	first->item = item;
	first->next = *this;
	*this = first;
	return 0;
}

int stack_pop(stack **this){	//"pop" first element from stack
	assert(*this != NULL);	//test *this
	stack *first = *this;	//temp. var for freeing memory
	int i = (*first)->item; //using first instead of this to clarify context
	*this = (*first)->next;	//giving back remaining stack without first element
	free(first);	//free memory for former element
	return i;	//return value of former first element
}

int stack_isempty(stack **this){
	return *this == NULL;
/*
	if(!*s) {	// *s == NULL
		return 1;	//stack is empty
	}
	return 0;
*/
}
