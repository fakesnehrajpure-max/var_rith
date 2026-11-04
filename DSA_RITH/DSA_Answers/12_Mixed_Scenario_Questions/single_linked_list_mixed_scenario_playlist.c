/* SINGLY LINKED LIST - MIXED SCENARIO
   A music playlist stores song IDs in a singly linked list.
   1) Remove duplicate songs (keep first occurrence).
   2) Find the middle song in ONE pass (slow/fast pointers).
   3) Reverse the playlist in place (iterative).
   4) Detect whether a bug has created a loop in the playlist (Floyd's cycle check). */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id;
	struct node *next;
}node;

/****function declarations****/
node *createNode(int id);
void insert_at_end(node **head, int id);
void display(node *head);
void remove_duplicates(node *head);
void middle(node *head);
void reverse(node **head);
int has_loop(node *head);
void free_list(node **head);

int main()
{
	node *head = NULL;
	int n, id;
	printf("give number of songs:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid count\n");
		return 1;
	}
	printf("give %d song IDs:\t", n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &id);
		insert_at_end(&head, id);
	}

	remove_duplicates(head);
	printf("without duplicates: ");
	display(head);
	middle(head);
	reverse(&head);
	printf("reversed: ");
	display(head);

	if(has_loop(head))
		printf("loop present\n");
	else
		printf("no loop\n");

	node *last = head;			/* make a loop on purpose to test the check */
	while(last->next != NULL)
		last = last->next;
	last->next = head;
	if(has_loop(head))
		printf("after creating a loop on purpose: loop present\n");
	last->next = NULL;			/* break it again before freeing */

	free_list(&head);
	return 0;
}

node *createNode(int id)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return NULL;
	}
	new_node->id = id;
	new_node->next = NULL;
	return new_node;
}

void insert_at_end(node **head, int id)
{
	node *new_node = createNode(id);
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
	q->next = new_node;
}

void display(node *head)
{
	for(node *q = head; q != NULL; q = q->next)
		printf("%d -> ", q->id);
	printf("NULL\n");
}

/* for every song a, delete any later node with the same id */
void remove_duplicates(node *head)
{
	for(node *a = head; a != NULL; a = a->next)
	{
		node *r = a;
		while(r->next != NULL)
		{
			if(r->next->id == a->id)
			{
				node *temp = r->next;
				r->next = temp->next;	/* unlink, then free */
				free(temp);
			}
			else
				r = r->next;
		}
	}
}

/* fast moves 2, slow moves 1: when fast reaches the end, slow is in the middle */
void middle(node *head)
{
	node *slow = head, *fast = head;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	printf("middle song: %d\n", slow->id);
}

void reverse(node **head)
{
	node *prev = NULL, *cur = *head, *nxt;
	while(cur != NULL)
	{
		nxt = cur->next;	/* save the rest */
		cur->next = prev;	/* turn the arrow back */
		prev = cur;
		cur = nxt;
	}
	*head = prev;
}

/* if there is a loop, fast will catch up with slow */
int has_loop(node *head)
{
	node *slow = head, *fast = head;
	while(fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
		if(slow == fast)
			return 1;
	}
	return 0;
}

void free_list(node **head)
{
	node *temp;
	while(*head != NULL)
	{
		temp = *head;
		*head = temp->next;
		free(temp);
	}
}
