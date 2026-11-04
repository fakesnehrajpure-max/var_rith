/* Day 9 Q1
   WAP to create an array of size 10 and store user defined integer values using hashing.
   Implement hashCode(), Insert(value), Search(value).
   (Collisions are handled with linear probing: if the slot is taken, try the next one.) */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define EMPTY -1
#define EXIT 0

/****function declarations****/
int hash_code(int value);
void Insert(int *p, int value);
void Search(int *p, int value);
void display(int *p);

int main()
{
	int choice, value;
	int *p = malloc(SIZE * sizeof(int));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	for(int *q = p; q < p + SIZE; q++)
		*q = EMPTY;

	do
	{
		printf("\n0.exit\n1.insert\n2.search\n3.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value (not negative):\t");
				scanf("%d", &value);
				if(value < 0)
					printf("only values >= 0\n");
				else
					Insert(p, value);
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				Search(p, value);
				break;
			case 3: display(p); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free(p);
	return 0;
}

int hash_code(int value)
{
	return value % SIZE;
}

void Insert(int *p, int value)
{
	int index = hash_code(value);
	for(int i = 0; i < SIZE; i++)
	{
		if(*(p + index) == EMPTY)
		{
			*(p + index) = value;
			printf("%d stored at index %d\n", value, index);
			return;
		}
		index = (index + 1) % SIZE;	/* collision: try the next slot, wrap around */
	}
	printf("hash table is full\n");
}

void Search(int *p, int value)
{
	int index = hash_code(value);
	for(int i = 0; i < SIZE; i++)
	{
		if(*(p + index) == EMPTY)	/* empty slot on the probe path: not present */
			break;
		if(*(p + index) == value)
		{
			printf("%d found at index %d\n", value, index);
			return;
		}
		index = (index + 1) % SIZE;
	}
	printf("%d not found\n", value);
}

void display(int *p)
{
	for(int *q = p; q < p + SIZE; q++)
	{
		if(*q == EMPTY)
			printf("%td: -\n", q - p);
		else
			printf("%td: %d\n", q - p, *q);
	}
}
