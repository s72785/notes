//#include "stack.h"
typedef stack_t {
	int item;
	stack_t next;
} stack;

void stack_push(stack **this, int item){
	stack *curr;
	curr = (stack*) malloc(sizeof(stack));
	curr->item = item;
	curr->next = *this;
	*this = curr;
}

int stack_pop(stack **this){
	assert(*this != NULL);
	stack *top;
	int i = (*this)->item;
	top = *this;
	*this = (*this)->next;
	free(top);
	return i;
}

int stack_isempty(stack **this){
	return *this == NULL;
}
