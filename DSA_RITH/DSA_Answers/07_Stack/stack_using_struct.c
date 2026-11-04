/* Day 6 Q2 (in C)
   Implement a stack of integer values. (The original question asks for a C++ class; C has
   no classes, so the stack is a struct STACK with runtime memory and functions that take STACK *s.)
   Create a menu driven program to push, pop, display values.
   Implement other essential methods like initStack(), isEmpty(), isFull(). */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct
{
	int *stack;
	int size;
	int top;
}STACK;

/****function declarations****/
int initStack(STACK *s, int size);
int isFull(STACK *s);
int isEmpty(STACK *s);
void push(STACK *s, int value);
void pop(STACK *s);
void display(STACK *s);

int main()
{
	STACK s;
	int size, choice, value;
	printf("give stack size:\t");
	scanf("%d", &size);
	if(size <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	if(initStack(&s, size) == 1)
		return 1;

	do
	{
		printf("\n0.exit\n1.push\n2.pop\n3.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				push(&s, value);
				break;
			case 2: pop(&s); break;
			case 3: display(&s); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free(s.stack);
	return 0;
}

int initStack(STACK *s, int size)
{
	s->stack = malloc(size * sizeof(int));
	if(s->stack == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	s->size = size;
	s->top = -1;
	return 0;
}

int isFull(STACK *s)
{
	if(s->top == s->size - 1)
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

void push(STACK *s, int value)
{
	if(isFull(s))
	{
		printf("stack overflow\n");
		return;
	}
	s->top++;
	*(s->stack + s->top) = value;
}

void pop(STACK *s)
{
	if(isEmpty(s))
	{
		printf("stack underflow\n");
		return;
	}
	printf("popped: %d\n", *(s->stack + s->top));
	s->top--;
}

void display(STACK *s)
{
	if(isEmpty(s))
	{
		printf("stack is empty\n");
		return;
	}
	printf("top -> ");
	for(int *q = s->stack + s->top; q >= s->stack; q--)
		printf("%d\t", *q);
	printf("\n");
}
