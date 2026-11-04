/* STACK - MIXED SCENARIO
   A calculator app receives an expression.
   1) Check the brackets ( ) [ ] { } are balanced.
   2) Convert the infix expression with single-digit operands to postfix.
   3) Evaluate the postfix expression.
   Example: (2+3)*4-6/2  ->  23+4*62/-  ->  17 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

typedef struct
{
	int stack[SIZE];
	int top;
}STACK;

/****function declarations****/
void initStack(STACK *s);
int isEmpty(STACK *s);
void push(STACK *s, int value);
int pop(STACK *s);
int peek(STACK *s);
int balanced(char *e);
int precedence(char ch);
void to_postfix(char *e, char *out);
int evaluate(char *post);

int main()
{
	char e[SIZE], post[SIZE];
	printf("give expression (no spaces):\t");
	scanf("%99s", e);
	if(balanced(e) == 0)
	{
		printf("brackets NOT balanced\n");
		return 0;
	}
	printf("balanced\n");
	to_postfix(e, post);
	printf("postfix: %s\n", post);
	printf("result: %d\n", evaluate(post));
	return 0;
}

void initStack(STACK *s)
{
	s->top = -1;
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
	if(s->top == SIZE - 1)
	{
		printf("stack overflow\n");
		return;
	}
	s->top++;
	*(s->stack + s->top) = value;
}

int pop(STACK *s)
{
	int value = *(s->stack + s->top);
	s->top--;
	return value;
}

int peek(STACK *s)
{
	return *(s->stack + s->top);
}

int balanced(char *e)
{
	STACK s;
	char open;
	initStack(&s);
	for(char *q = e; *q != '\0'; q++)
	{
		if(*q == '(' || *q == '[' || *q == '{')
			push(&s, *q);
		else if(*q == ')' || *q == ']' || *q == '}')
		{
			if(isEmpty(&s))
				return 0;		/* closing with nothing open */
			open = pop(&s);
			if(*q == ')' && open != '(')
				return 0;
			else if(*q == ']' && open != '[')
				return 0;
			else if(*q == '}' && open != '{')
				return 0;
		}
	}
	if(isEmpty(&s))
		return 1;
	else
		return 0;			/* something left open */
}

int precedence(char ch)
{
	if(ch == '*' || ch == '/')
		return 2;
	else if(ch == '+' || ch == '-')
		return 1;
	else
		return 0;
}

void to_postfix(char *e, char *out)
{
	STACK s;
	char *w = out;
	initStack(&s);
	for(char *q = e; *q != '\0'; q++)
	{
		if(*q >= '0' && *q <= '9')		/* operand goes straight out */
			*w++ = *q;
		else if(*q == '(' || *q == '[' || *q == '{')
			push(&s, '(');
		else if(*q == ')' || *q == ']' || *q == '}')
		{
			while(peek(&s) != '(')		/* pop until the matching open */
				*w++ = pop(&s);
			pop(&s);
		}
		else if(precedence(*q) > 0)
		{
			while(!isEmpty(&s) && precedence(peek(&s)) >= precedence(*q))
				*w++ = pop(&s);
			push(&s, *q);
		}
	}
	while(!isEmpty(&s))
		*w++ = pop(&s);
	*w = '\0';
}

int evaluate(char *post)
{
	STACK s;
	int a, b;
	initStack(&s);
	for(char *q = post; *q != '\0'; q++)
	{
		if(*q >= '0' && *q <= '9')
		{
			push(&s, *q - '0');
			continue;
		}
		b = pop(&s);			/* right operand comes out first */
		a = pop(&s);
		if(*q == '+')
			push(&s, a + b);
		else if(*q == '-')
			push(&s, a - b);
		else if(*q == '*')
			push(&s, a * b);
		else
			push(&s, a / b);
	}
	return pop(&s);
}
