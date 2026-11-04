/* Day 8 Q2
   Implement a menu driven program to implement a Dynamic Queue, i.e. a queue using a linked
   list to store integer values, and perform the following operations:
   void EnQueue(value, &front, &rear) : pass pointers by address
   int DeQueue(&front, &rear)         : pass pointers by address
   int Front(front)                   : display the 1st value, pass by value
   int Rear(rear)                     : display the last value, pass by value
   void Display()
   int isEmpty(front, rear)
   node createNode() */

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
void EnQueue(int value, node **front, node **rear);
int DeQueue(node **front, node **rear);
int Front(node *front);
int Rear(node *rear);
void Display(node *front);
int isEmpty(node *front, node *rear);

int main()
{
	node *front = NULL, *rear = NULL;
	int choice, value;

	do
	{
		printf("\n0.exit\n1.enqueue\n2.dequeue\n3.front\n4.rear\n5.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				EnQueue(value, &front, &rear);
				break;
			case 2:
				if(isEmpty(front, rear))
					printf("queue is empty\n");
				else
					printf("dequeued: %d\n", DeQueue(&front, &rear));
				break;
			case 3:
				if(isEmpty(front, rear))
					printf("queue is empty\n");
				else
					printf("front: %d\n", Front(front));
				break;
			case 4:
				if(isEmpty(front, rear))
					printf("queue is empty\n");
				else
					printf("rear: %d\n", Rear(rear));
				break;
			case 5: Display(front); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	while(!isEmpty(front, rear))
		DeQueue(&front, &rear);
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

/* add at rear */
void EnQueue(int value, node **front, node **rear)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	if(*rear == NULL)			/* empty queue: both point to the new node */
	{
		*front = new_node;
		*rear = new_node;
		return;
	}
	(*rear)->next = new_node;
	*rear = new_node;
}

/* remove at front; main checks isEmpty first */
int DeQueue(node **front, node **rear)
{
	node *temp = *front;
	int value = temp->data;
	*front = temp->next;
	if(*front == NULL)			/* queue became empty */
		*rear = NULL;
	free(temp);
	return value;
}

int Front(node *front)
{
	return front->data;
}

int Rear(node *rear)
{
	return rear->data;
}

void Display(node *front)
{
	if(front == NULL)
	{
		printf("queue is empty\n");
		return;
	}
	printf("front -> ");
	for(node *q = front; q != NULL; q = q->next)
		printf("%d\t", q->data);
	printf("<- rear\n");
}

int isEmpty(node *front, node *rear)
{
	if(front == NULL && rear == NULL)
		return 1;
	else
		return 0;
}
