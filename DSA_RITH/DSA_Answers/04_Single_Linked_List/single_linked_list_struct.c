/* Day 6 Q3 (in C)
   Implement a singly linked list to store integer values.
   (The original question asks for a C++ class; C has no classes, so the list is a struct
   LIST that holds head, and every "method" is a function that takes LIST *l.)
   Implement methods:
   addNode    (this method will add node only at end of LL)
   deleteNode (this method will delete only last node of LL)
   display    (to print all nodes of LL) */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct node
{
	int data;
	struct node *next;
}node;

typedef struct
{
	node *head;
}LIST;

/****function declarations****/
void initList(LIST *l);
void addNode(LIST *l, int value);
void deleteNode(LIST *l);
void display(LIST *l);

int main()
{
	LIST l;
	int choice, value;
	initList(&l);

	do
	{
		printf("\n0.exit\n1.add node (at end)\n2.delete node (last)\n3.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				addNode(&l, value);
				break;
			case 2: deleteNode(&l); break;
			case 3: display(&l); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	while(l.head != NULL)
		deleteNode(&l);
	return 0;
}

void initList(LIST *l)
{
	l->head = NULL;
}

void addNode(LIST *l, int value)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	new_node->data = value;
	new_node->next = NULL;
	if(l->head == NULL)
	{
		l->head = new_node;
		return;
	}
	node *q = l->head;
	while(q->next != NULL)
		q = q->next;
	q->next = new_node;
}

void deleteNode(LIST *l)
{
	if(l->head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	if(l->head->next == NULL)
	{
		free(l->head);
		l->head = NULL;
		return;
	}
	node *q = l->head;
	while(q->next->next != NULL)
		q = q->next;
	free(q->next);
	q->next = NULL;
}

void display(LIST *l)
{
	if(l->head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	for(node *q = l->head; q != NULL; q = q->next)
		printf("%d -> ", q->data);
	printf("NULL\n");
}
