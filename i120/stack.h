//#include "stack.h"
typedef struct stack_t {
	int item;	// value for element on stack
	stack_t *next;	// pointer on next element on stack (recursive)
} stack;	// name of data type

int stack_push(stack **this, int item);

int stack_pop(stack **this);

int stack_isempty(stack **this);
