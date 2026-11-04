/* Day 5 Q2
   WAP to implement a circular queue using arrays.
   (Use a structure, runtime memory, menu driven.) */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct
{
	int size;
	int *queue;
	int front;
	int rear;
	int count;
}Q;

/****function declarations****/
int initQueue(Q *p, int size);
int isFull(Q *p);
int isEmpty(Q *p);
void enQueue(Q *p, int value);
void deQueue(Q *p);
void display(Q *p);

int main()
{
	Q q;
	int size, choice, value;
	printf("give queue size:\t");
	scanf("%d", &size);
	if(size <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	if(initQueue(&q, size) == 1)
		return 1;

	do
	{
		printf("\n0.exit\n1.enQueue\n2.deQueue\n3.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				enQueue(&q, value);
				break;
			case 2: deQueue(&q); break;
			case 3: display(&q); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free(q.queue);
	return 0;
}

int initQueue(Q *p, int size)
{
	p->queue = malloc(size * sizeof(int));
	if(p->queue == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	p->size = size;
	p->front = 0;
	p->rear = -1;
	p->count = 0;
	return 0;
}

int isFull(Q *p)
{
	if(p->count == p->size)
		return 1;
	else
		return 0;
}

int isEmpty(Q *p)
{
	if(p->count == 0)
		return 1;
	else
		return 0;
}

void enQueue(Q *p, int value)
{
	if(isFull(p))
	{
		printf("queue is full\n");
		return;
	}
	p->rear = (p->rear + 1) % p->size;	/* wrap around to 0 after the last slot */
	*(p->queue + p->rear) = value;
	p->count++;
}

void deQueue(Q *p)
{
	if(isEmpty(p))
	{
		printf("queue is empty\n");
		return;
	}
	printf("dequeued: %d\n", *(p->queue + p->front));
	p->front = (p->front + 1) % p->size;
	p->count--;
}

void display(Q *p)
{
	if(isEmpty(p))
	{
		printf("queue is empty\n");
		return;
	}
	int index = p->front;
	printf("front -> ");
	for(int k = 0; k < p->count; k++)	/* walk count items, wrapping */
	{
		printf("%d\t", *(p->queue + index));
		index = (index + 1) % p->size;
	}
	printf("<- rear\n");
}
