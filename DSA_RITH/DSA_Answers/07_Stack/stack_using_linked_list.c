/* Day 8 Q1
   Implement a menu driven program to implement a Dynamic stack, i.e. a stack using a linked
   list to store integer values, and perform the following operations:
   void Push(value, &top) : pass *top by address
   int Pop(&top)          : pass *top by address
   int Pick(top)          : only reads the topmost value, pass *top by value
   void Display(top)      : pass *top by value
   int isEmpty(top)
   node createNode()      : returns the new node created */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct node
{
	int data;
	struct node *next;
}node;

/****function declarations****/
node *createNode(int value);
void Push(int value, node **top);
int Pop(node **top);
int Pick(node *top);
void Display(node *top);
int isEmpty(node *top);

int main()
{
	node *top = NULL;
	int choice, value;

	do
	{
		printf("\n0.exit\n1.push\n2.pop\n3.pick\n4.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				Push(value, &top);
				break;
			case 2:
				if(isEmpty(top))
					printf("stack underflow\n");
				else
					printf("popped: %d\n", Pop(&top));
				break;
			case 3:
				if(isEmpty(top))
					printf("stack is empty\n");
				else
					printf("top: %d\n", Pick(top));
				break;
			case 4: Display(top); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	while(!isEmpty(top))
		Pop(&top);
	return 0;
}

node *createNode(int value)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return NULL;
	}
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}

/* push = insert at beginning: top changes, so double pointer */
void Push(int value, node **top)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	new_node->next = *top;
	*top = new_node;
}

/* pop = delete at beginning; main checks isEmpty first */
int Pop(node **top)
{
	node *temp = *top;
	int value = temp->data;
	*top = temp->next;
	free(temp);
	return value;
}

int Pick(node *top)
{
	return top->data;
}

void Display(node *top)
{
	if(isEmpty(top))
	{
		printf("stack is empty\n");
		return;
	}
	printf("top -> ");
	for(node *q = top; q != NULL; q = q->next)
		printf("%d\t", q->data);
	printf("\n");
}

int isEmpty(node *top)
{
	if(top == NULL)
		return 1;
	else
		return 0;
}
