/* CIRCULAR LINKED LIST - MIXED SCENARIO
   Round-robin CPU scheduler: each task has an ID and burst time.
   Time quantum = Q. The CPU gives each task Q units in turn (circular).
   When a task finishes, remove it from the circle and print its finish time.
   (Same idea as the Josephus problem.) */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int id;
	int remaining;
	struct node *next;
}node;

/****function declarations****/
void add_task(node **last, int id, int burst);
void schedule(node **last, int quantum);

int main()
{
	node *last = NULL;		/* last->next is the first task */
	int n, quantum, burst;
	printf("give number of tasks and quantum:\t");
	scanf("%d %d", &n, &quantum);
	if(n <= 0 || quantum <= 0)
	{
		printf("invalid input\n");
		return 1;
	}
	for(int i = 1; i <= n; i++)
	{
		printf("burst time of task %d:\t", i);
		scanf("%d", &burst);
		add_task(&last, i, burst);
	}
	schedule(&last, quantum);
	return 0;
}

void add_task(node **last, int id, int burst)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	new_node->id = id;
	new_node->remaining = burst;
	if(*last == NULL)
	{
		new_node->next = new_node;	/* one task points to itself */
		*last = new_node;
		return;
	}
	new_node->next = (*last)->next;		/* add after last, then it becomes last */
	(*last)->next = new_node;
	*last = new_node;
}

void schedule(node **last, int quantum)
{
	int clock = 0, run;
	node *prev = *last, *cur = (*last)->next;
	printf("\n");
	while(cur != NULL)
	{
		if(cur->remaining < quantum)
			run = cur->remaining;
		else
			run = quantum;
		clock = clock + run;
		cur->remaining = cur->remaining - run;

		if(cur->remaining == 0)
		{
			printf("task %d finished at time %d\n", cur->id, clock);
			if(cur->next == cur)		/* it was the last task */
			{
				free(cur);
				cur = NULL;
				*last = NULL;
			}
			else
			{
				prev->next = cur->next;	/* unlink, then free */
				free(cur);
				cur = prev->next;
			}
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}
