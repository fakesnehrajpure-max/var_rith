/* QUEUE - MIXED SCENARIO
   An office printer queue (circular queue of size 5) receives print jobs with page counts.
   1) Jobs arrive and are printed in FIFO order; reject a job when the queue is full.
   2) Printer prints 3 pages per second: print the finishing time of each job.
   3) Manager wants the remaining jobs reversed (use a STACK to reverse the QUEUE). */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

typedef struct
{
	int queue[SIZE];
	int front;
	int rear;
	int count;
}Q;

typedef struct
{
	int stack[SIZE];
	int top;
}STACK;

/****function declarations****/
void initQueue(Q *p);
int isFull(Q *p);
int isEmpty(Q *p);
void enQueue(Q *p, int pages);
int deQueue(Q *p);
void display(Q *p);
void print_jobs(Q *p, int k);
void reverse_queue(Q *p);

int main()
{
	Q q;
	int n, pages, k;
	initQueue(&q);

	printf("give number of jobs arriving:\t");
	scanf("%d", &n);
	for(int i = 0; i < n; i++)
	{
		printf("pages of job %d:\t", i + 1);
		scanf("%d", &pages);
		enQueue(&q, pages);
	}
	printf("give how many jobs to print now:\t");
	scanf("%d", &k);
	print_jobs(&q, k);
	reverse_queue(&q);
	return 0;
}

void initQueue(Q *p)
{
	p->front = 0;
	p->rear = -1;
	p->count = 0;
}

int isFull(Q *p)
{
	if(p->count == SIZE)
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

void enQueue(Q *p, int pages)
{
	if(isFull(p))
	{
		printf("queue full, job rejected\n");
		return;
	}
	p->rear = (p->rear + 1) % SIZE;
	*(p->queue + p->rear) = pages;
	p->count++;
}

/* caller checks isEmpty first */
int deQueue(Q *p)
{
	int pages = *(p->queue + p->front);
	p->front = (p->front + 1) % SIZE;
	p->count--;
	return pages;
}

void display(Q *p)
{
	int index = p->front;
	for(int k = 0; k < p->count; k++)
	{
		printf("%d\t", *(p->queue + index));
		index = (index + 1) % SIZE;
	}
	printf("\n");
}

void print_jobs(Q *p, int k)
{
	float time = 0;
	int pages;
	for(int i = 0; i < k && !isEmpty(p); i++)
	{
		pages = deQueue(p);
		time = time + pages / 3.0;
		printf("job of %d pages done at %.2f s\n", pages, time);
	}
}

/* queue -> stack -> queue reverses the order */
void reverse_queue(Q *p)
{
	STACK s;
	s.top = -1;
	while(!isEmpty(p))
	{
		s.top++;
		*(s.stack + s.top) = deQueue(p);
	}
	while(s.top >= 0)
	{
		enQueue(p, *(s.stack + s.top));
		s.top--;
	}
	printf("remaining jobs reversed: ");
	display(p);
}
