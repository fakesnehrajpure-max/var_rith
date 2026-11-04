/* Day 4 Q3
   WAP to create a stack of characters in order to store alphabets A-Z
   and print them in reverse order. */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 26

typedef struct
{
	char stack[SIZE];
	int top;
}STACK;

/****function declarations****/
void initStack(STACK *s);
int isFull(STACK *s);
int isEmpty(STACK *s);
void push(STACK *s, char ch);
void pop(STACK *s);

int main()
{
	STACK s;
	initStack(&s);

	for(char ch = 'A'; ch <= 'Z'; ch++)
		push(&s, ch);

	printf("reverse: ");
	while(!isEmpty(&s))
		pop(&s);			/* last in, first out: Z comes out first */
	printf("\n");
	return 0;
}

void initStack(STACK *s)
{
	s->top = -1;
}

int isFull(STACK *s)
{
	if(s->top == SIZE - 1)
		return 1;
	else
		return 0;
}

int isEmpty(STACK *s)
{
	if(s->top == -1)
		return 1;
	else
		return 0;
}

void push(STACK *s, char ch)
{
	if(isFull(s))
	{
		printf("stack overflow\n");
		return;
	}
	s->top++;
	*(s->stack + s->top) = ch;
}

void pop(STACK *s)
{
	if(isEmpty(s))
	{
		printf("stack underflow\n");
		return;
	}
	printf("%c ", *(s->stack + s->top));
	s->top--;
}
