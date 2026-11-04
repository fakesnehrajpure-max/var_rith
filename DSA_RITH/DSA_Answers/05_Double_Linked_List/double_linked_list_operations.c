/* Day 4 Q4
   WAP to implement a doubly linked list with the following operations:
   createNode()
   addAtStart()
   addAtEnd()
   addAtMiddle()     this must add the new value after the node mentioned by the user
   deleteAtStart()
   deleteAtEnd()
   deleteAtMiddle()  this must delete the node mentioned by the user
   display() */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}node;

/****function declarations****/
node *createNode(int value);
void addAtStart(node **head, int value);
void addAtEnd(node **head, int value);
void addAtMiddle(node *head, int key, int value);
void deleteAtStart(node **head);
void deleteAtEnd(node **head);
void deleteAtMiddle(node **head, int key);
void display(node *head);

int main()
{
	node *head = NULL;
	int choice, value, key;

	do
	{
		printf("\n0.exit\n1.add at start\n2.add at end\n3.add after a value\n4.delete at start\n");
		printf("5.delete at end\n6.delete a value\n7.display\n");
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
			case 3:
				printf("add after which value, new value:\t");
				scanf("%d %d", &key, &value);
				addAtMiddle(head, key, value);
				break;
			case 4: deleteAtStart(&head); break;
			case 5: deleteAtEnd(&head); break;
			case 6:
				printf("give value to delete:\t");
				scanf("%d", &key);
				deleteAtMiddle(&head, key);
				break;
			case 7: display(head); break;
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
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void addAtStart(node **head, int value)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	new_node->next = *head;			/* new -> old first */
	if(*head != NULL)
		(*head)->prev = new_node;	/* old first <- new */
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
	node *q = *head;
	while(q->next != NULL)
		q = q->next;
	q->next = new_node;			/* link both ways */
	new_node->prev = q;
}

void addAtMiddle(node *head, int key, int value)
{
	node *q = head;
	while(q != NULL && q->data != key)
		q = q->next;
	if(q == NULL)
	{
		printf("%d not found\n", key);
		return;
	}
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	new_node->next = q->next;
	new_node->prev = q;
	if(q->next != NULL)
		q->next->prev = new_node;
	q->next = new_node;
}

void deleteAtStart(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *temp = *head;
	*head = temp->next;
	if(*head != NULL)
		(*head)->prev = NULL;		/* new first node has no prev */
	free(temp);
}

void deleteAtEnd(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *q = *head;
	while(q->next != NULL)
		q = q->next;
	if(q->prev == NULL)			/* only one node */
		*head = NULL;
	else
		q->prev->next = NULL;		/* second-last becomes last */
	free(q);
}

void deleteAtMiddle(node **head, int key)
{
	node *q = *head;
	while(q != NULL && q->data != key)
		q = q->next;
	if(q == NULL)
	{
		printf("%d not found\n", key);
		return;
	}
	if(q->prev != NULL)
		q->prev->next = q->next;	/* forward link skips q */
	else
		*head = q->next;
	if(q->next != NULL)
		q->next->prev = q->prev;	/* backward link skips q */
	free(q);
}

void display(node *head)
{
	if(head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *last = head;
	printf("forward : ");
	for(node *q = head; q != NULL; q = q->next)
	{
		printf("%d <-> ", q->data);
		last = q;
	}
	printf("NULL\nbackward: ");
	for(node *q = last; q != NULL; q = q->prev)
		printf("%d <-> ", q->data);
	printf("NULL\n");
}
