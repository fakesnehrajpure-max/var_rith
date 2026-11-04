/* Day 5 Q1
   WAP to implement a user defined Queue using an array.
   Accept the size of the queue from the user and allocate memory for the queue at runtime.
   Make use of a structure to store queue size, memory, front and rear.
   Create a menu driven program providing options to initQueue, enQueue, deQueue, display.
   Implement other required functions isFull(), isEmpty(). */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct
{
	int size;
	int *queue;
	int front;
	int rear;
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
	int choice, value, size;
	q.queue = NULL;

	do
	{
		printf("\n0.exit\n1.initQueue\n2.enQueue\n3.deQueue\n4.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		if(choice >= 2 && choice <= 4 && q.queue == NULL)
		{
			printf("call initQueue first\n");
			continue;
		}
		switch(choice)
		{
			case 1:
				printf("give queue size:\t");
				scanf("%d", &size);
				if(size <= 0)
				{
					printf("invalid size\n");
					break;
				}
				free(q.queue);			/* re-init: drop the old memory */
				if(initQueue(&q, size) == 1)
					return 1;
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				enQueue(&q, value);
				break;
			case 3: deQueue(&q); break;
			case 4: display(&q); break;
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
	return 0;
}

int isFull(Q *p)
{
	if(p->rear == p->size - 1)
		return 1;
	else
		return 0;
}

int isEmpty(Q *p)
{
	if(p->front > p->rear)
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
	p->rear++;				/* enqueue moves only rear */
	*(p->queue + p->rear) = value;
}

void deQueue(Q *p)
{
	if(isEmpty(p))
	{
		printf("queue is empty\n");
		return;
	}
	printf("dequeued: %d\n", *(p->queue + p->front));
	p->front++;				/* dequeue moves only front */
}

void display(Q *p)
{
	if(isEmpty(p))
	{
		printf("queue is empty\n");
		return;
	}
	printf("front -> ");
	for(int *q = p->queue + p->front; q <= p->queue + p->rear; q++)
		printf("%d\t", *q);
	printf("<- rear\n");
}
