/* DOUBLY LINKED LIST - MIXED SCENARIO
   Browser history: visit(page), back(steps), forward(steps).
   Visiting a new page after going back must DELETE all forward history.
   Use a doubly linked list so back and forward are both O(1) per step. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT 0

typedef struct node
{
	char url[50];
	struct node *prev;
	struct node *next;
}node;

/****function declarations****/
void visit(node **cur, char *url);
void back(node **cur, int steps);
void forward(node **cur, int steps);
void show(node *cur);
void free_history(node **cur);

int main()
{
	node *cur = NULL;
	int choice, steps;
	char url[50];

	do
	{
		printf("\n0.exit\n1.visit\n2.back\n3.forward\n4.show history\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give url:\t");
				scanf("%49s", url);
				visit(&cur, url);
				break;
			case 2:
				printf("give steps:\t");
				scanf("%d", &steps);
				back(&cur, steps);
				break;
			case 3:
				printf("give steps:\t");
				scanf("%d", &steps);
				forward(&cur, steps);
				break;
			case 4: show(cur); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
		if(choice >= 1 && choice <= 3 && cur != NULL)
			printf("now on: %s\n", cur->url);
	}while(choice != EXIT);

	free_history(&cur);
	return 0;
}

void visit(node **cur, char *url)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	strcpy(new_node->url, url);
	new_node->prev = *cur;
	new_node->next = NULL;
	if(*cur != NULL)
	{
		node *f = (*cur)->next;		/* drop all forward history */
		while(f != NULL)
		{
			node *temp = f;
			f = f->next;
			free(temp);
		}
		(*cur)->next = new_node;
	}
	*cur = new_node;
}

void back(node **cur, int steps)
{
	while(steps > 0 && *cur != NULL && (*cur)->prev != NULL)
	{
		*cur = (*cur)->prev;
		steps--;
	}
}

void forward(node **cur, int steps)
{
	while(steps > 0 && *cur != NULL && (*cur)->next != NULL)
	{
		*cur = (*cur)->next;
		steps--;
	}
}

void show(node *cur)
{
	if(cur == NULL)
	{
		printf("no history\n");
		return;
	}
	node *first = cur;
	while(first->prev != NULL)
		first = first->prev;
	for(node *q = first; q != NULL; q = q->next)
	{
		if(q == cur)
			printf("[%s] <-> ", q->url);
		else
			printf("%s <-> ", q->url);
	}
	printf("END\n");
}

void free_history(node **cur)
{
	if(*cur == NULL)
		return;
	node *q = *cur;
	while(q->prev != NULL)
		q = q->prev;
	while(q != NULL)
	{
		node *temp = q;
		q = q->next;
		free(temp);
	}
	*cur = NULL;
}
