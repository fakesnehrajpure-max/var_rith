/* Assignment 2 (DS) Q2
   Write a C program to implement Binary Search. Check for duplicate inputs: if found, do not
   insert into the array. The array must be kept in sorted order: insert each element at its
   right position (index), shifting elements as needed, and discard duplicates.
   Apply an appropriate condition check for the element-not-found scenario.
   (a) Binary search (iterative)   (b) Binary search (recursion) */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

/****function declarations****/
int *binary_iter(int *p, int n, int value);
int *binary_rec(int *low, int *high, int value);
void insert_sorted(int *p, int *n, int size, int value);
void display(int *p, int n);

int main()
{
	int size, n = 0, choice, value;
	int *pos;
	printf("give max size:\t");
	scanf("%d", &size);
	if(size <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int *p = malloc(size * sizeof(int));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}

	do
	{
		printf("\n0.exit\n1.insert\n2.binary search iterative\n3.binary search recursive\n4.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				insert_sorted(p, &n, size, value);
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				pos = binary_iter(p, n, value);
				if(pos == NULL)
					printf("%d not found\n", value);
				else
					printf("%d found at index %td\n", value, pos - p);
				break;
			case 3:
				printf("give value:\t");
				scanf("%d", &value);
				pos = binary_rec(p, p + n - 1, value);
				if(pos == NULL)
					printf("%d not found\n", value);
				else
					printf("%d found at index %td\n", value, pos - p);
				break;
			case 4: display(p, n); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free(p);
	return 0;
}

int *binary_iter(int *p, int n, int value)
{
	int *low = p, *high = p + n - 1, *mid;
	while(low <= high)
	{
		mid = low + (high - low) / 2;
		if(*mid == value)
			return mid;
		else if(*mid < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return NULL;
}

int *binary_rec(int *low, int *high, int value)
{
	if(low > high)
		return NULL;
	int *mid = low + (high - low) / 2;
	if(*mid == value)
		return mid;
	else if(*mid < value)
		return binary_rec(mid + 1, high, value);
	else
		return binary_rec(low, mid - 1, value);
}

void insert_sorted(int *p, int *n, int size, int value)
{
	if(*n == size)
	{
		printf("array is full\n");
		return;
	}
	if(binary_iter(p, *n, value) != NULL)
	{
		printf("duplicate %d discarded\n", value);
		return;
	}
	int *q = p + *n - 1;
	while(q >= p && *q > value)		/* shift bigger values one place right */
	{
		*(q + 1) = *q;
		q--;
	}
	*(q + 1) = value;
	(*n)++;
}

void display(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
}
