/* Day 4 Q5
   WAP to implement a singly circular linked list with the following operations:
   createNode()
   addAtStart()
   addAtEnd()
   deleteAtStart()
   deleteAtEnd()
   display() */

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
void addAtStart(node **head, int value);
void addAtEnd(node **head, int value);
void deleteAtStart(node **head);
void deleteAtEnd(node **head);
void display(node *head);

int main()
{
	node *head = NULL;
	int choice, value;

	do
	{
		printf("\n0.exit\n1.add at start\n2.add at end\n3.delete at start\n4.delete at end\n5.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				addAtStart(&head, value);
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				addAtEnd(&head, value);
				break;
			case 3: deleteAtStart(&head); break;
			case 4: deleteAtEnd(&head); break;
			case 5: display(head); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	while(head != NULL)
		deleteAtStart(&head);
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
	new_node->next = new_node;		/* a single node points to itself */
	return new_node;
}

void addAtStart(node **head, int value)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	if(*head == NULL)
	{
		*head = new_node;
		return;
	}
	node *last = *head;
	while(last->next != *head)		/* last node points back to head */
		last = last->next;
	new_node->next = *head;
	last->next = new_node;
	*head = new_node;
}

void addAtEnd(node **head, int value)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	if(*head == NULL)
	{
		*head = new_node;
		return;
	}
	node *last = *head;
	while(last->next != *head)
		last = last->next;
	last->next = new_node;
	new_node->next = *head;			/* close the circle */
}

void deleteAtStart(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *temp = *head;
	if(temp->next == temp)			/* only one node */
	{
		*head = NULL;
		free(temp);
		return;
	}
	node *last = *head;
	while(last->next != *head)
		last = last->next;
	*head = temp->next;
	last->next = *head;
	free(temp);
}

void deleteAtEnd(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	if((*head)->next == *head)		/* only one node */
	{
		free(*head);
		*head = NULL;
		return;
	}
	node *q = *head;
	while(q->next->next != *head)		/* stop before the last node */
		q = q->next;
	free(q->next);
	q->next = *head;
}

void display(node *head)
{
	if(head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *q = head;
	do
	{
		printf("%d -> ", q->data);
		q = q->next;
	}while(q != head);			/* stop when we are back at head */
	printf("(back to %d)\n", head->data);
}
