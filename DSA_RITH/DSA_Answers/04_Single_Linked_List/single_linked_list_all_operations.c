/* Assignment 2: Linked List
   Write a C program to implement a linked list with one integer as data item and write the
   following functions:   struct node { int data; struct node *next; };
   1. Display the list
   2. Insert a node at the beginning of the list
   3. Insert a node at the end of the list
   4. Remove the node at the beginning of the list
   5. Remove the node at the end of the list
   6. Find number of nodes in the list
   7. Search a data in the list
   8. Insert a node at a given position in the list (e.g. insert a node at 3rd position)
   9. Delete a node at a given position in the list
   10. Insert a node after a node containing a given data item (e.g. after the node containing 12)
   11. Delete a node after a node containing a given data item
   12. Display the linked list in reverse (recursive)
   Note: in all the above functions take care of cases like linked list empty,
   linked list containing only one node etc. */

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
void display(node *head);
void insert_at_beg(node **head, int value);
void insert_at_end(node **head, int value);
void delete_at_beg(node **head);
void delete_at_end(node **head);
int count(node *head);
void search(node *head, int value);
void insert_at_pos(node **head, int value, int pos);
void delete_at_pos(node **head, int pos);
void insert_after_value(node *head, int key, int value);
void delete_after_value(node *head, int key);
void print_reverse(node *head);
void free_list(node **head);

int main()
{
	node *head = NULL;
	int choice, value, pos, key;

	do
	{
		printf("\n0.exit\n1.display\n2.insert at beginning\n3.insert at end\n4.delete at beginning\n");
		printf("5.delete at end\n6.count\n7.search\n8.insert at position\n9.delete at position\n");
		printf("10.insert after value\n11.delete after value\n12.display in reverse\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: display(head); break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				insert_at_beg(&head, value);
				break;
			case 3:
				printf("give value:\t");
				scanf("%d", &value);
				insert_at_end(&head, value);
				break;
			case 4: delete_at_beg(&head); break;
			case 5: delete_at_end(&head); break;
			case 6: printf("number of nodes = %d\n", count(head)); break;
			case 7:
				printf("give value:\t");
				scanf("%d", &value);
				search(head, value);
				break;
			case 8:
				printf("give value and position:\t");
				scanf("%d %d", &value, &pos);
				insert_at_pos(&head, value, pos);
				break;
			case 9:
				printf("give position:\t");
				scanf("%d", &pos);
				delete_at_pos(&head, pos);
				break;
			case 10:
				printf("insert after which value, new value:\t");
				scanf("%d %d", &key, &value);
				insert_after_value(head, key, value);
				break;
			case 11:
				printf("delete after which value:\t");
				scanf("%d", &key);
				delete_after_value(head, key);
				break;
			case 12:
				if(head == NULL)
					printf("list is empty");
				print_reverse(head);
				printf("\n");
				break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free_list(&head);
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

void display(node *head)
{
	if(head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	for(node *q = head; q != NULL; q = q->next)
		printf("%d -> ", q->data);
	printf("NULL\n");
}

void insert_at_beg(node **head, int value)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	new_node->next = *head;		/* connect first */
	*head = new_node;		/* then move head */
}

void insert_at_end(node **head, int value)
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
	while(q->next != NULL)		/* stop ON the last node */
		q = q->next;
	q->next = new_node;
}

void delete_at_beg(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	node *temp = *head;
	*head = temp->next;
	free(temp);
}

void delete_at_end(node **head)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	if((*head)->next == NULL)	/* only one node */
	{
		free(*head);
		*head = NULL;
		return;
	}
	node *q = *head;
	while(q->next->next != NULL)	/* stop BEFORE the last node */
		q = q->next;
	free(q->next);
	q->next = NULL;
}

int count(node *head)
{
	int c = 0;
	for(node *q = head; q != NULL; q = q->next)
		c++;
	return c;
}

void search(node *head, int value)
{
	int pos = 1;
	for(node *q = head; q != NULL; q = q->next)
	{
		if(q->data == value)
		{
			printf("%d found at position %d\n", value, pos);
			return;
		}
		pos++;
	}
	printf("%d not found\n", value);
}

void insert_at_pos(node **head, int value, int pos)
{
	if(pos == 1)
	{
		insert_at_beg(head, value);
		return;
	}
	if(pos < 1 || *head == NULL)
	{
		printf("invalid position\n");
		return;
	}
	node *q = *head;
	for(int i = 1; i < pos - 1 && q != NULL; i++)	/* walk to node pos-1 */
		q = q->next;
	if(q == NULL)
	{
		printf("invalid position\n");
		return;
	}
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	new_node->next = q->next;	/* connect first, then link */
	q->next = new_node;
}

void delete_at_pos(node **head, int pos)
{
	if(*head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	if(pos == 1)
	{
		delete_at_beg(head);
		return;
	}
	node *q = *head;
	for(int i = 1; i < pos - 1 && q != NULL; i++)
		q = q->next;
	if(pos < 1 || q == NULL || q->next == NULL)	/* check AFTER the walk */
	{
		printf("invalid position\n");
		return;
	}
	node *temp = q->next;
	q->next = temp->next;		/* unlink first */
	free(temp);			/* free last */
}

void insert_after_value(node *head, int key, int value)
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
	q->next = new_node;
}

void delete_after_value(node *head, int key)
{
	node *q = head;
	while(q != NULL && q->data != key)
		q = q->next;
	if(q == NULL)
	{
		printf("%d not found\n", key);
		return;
	}
	if(q->next == NULL)
	{
		printf("no node after %d\n", key);
		return;
	}
	node *temp = q->next;
	q->next = temp->next;
	free(temp);
}

void print_reverse(node *head)
{
	if(head == NULL)
		return;
	print_reverse(head->next);	/* recurse first, then print */
	printf("%d ", head->data);
}

void free_list(node **head)
{
	while(*head != NULL)
		delete_at_beg(head);
}
