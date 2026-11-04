/* Day 4 Q2
   WAP to implement a user defined Stack using an array to store integer values.
   Create a menu driven program providing options to push, pop, peek, display.
   Implement other required functions initStack(), isFull(), isEmpty(). */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5
#define EXIT 0

typedef struct
{
	int stack[SIZE];
	int top;
}STACK;

/****function declarations****/
void initStack(STACK *s);
int isFull(STACK *s);
int isEmpty(STACK *s);
void push(STACK *s, int value);
void pop(STACK *s);
void peek(STACK *s);
void display(STACK *s);

int main()
{
	STACK s;
	int choice, value;
	initStack(&s);

	do
	{
		printf("\n0.exit\n1.push\n2.pop\n3.peek\n4.display\n");
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
			case 3: peek(&s); break;
			case 4: display(&s); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

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

void push(STACK *s, int value)
{
	if(isFull(s))
	{
		printf("stack overflow\n");
		return;
	}
	s->top++;				/* move, then store */
	*(s->stack + s->top) = value;
}

void pop(STACK *s)
{
	if(isEmpty(s))
	{
		printf("stack underflow\n");
		return;
	}
	printf("popped: %d\n", *(s->stack + s->top));	/* read, then move */
	s->top--;
}

void peek(STACK *s)
{
	if(isEmpty(s))
	{
		printf("stack is empty\n");
		return;
	}
	printf("top: %d\n", *(s->stack + s->top));
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
