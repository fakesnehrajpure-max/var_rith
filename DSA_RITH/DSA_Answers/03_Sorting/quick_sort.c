/* Day 5 Q4
   Implement a program to accept a list of elements from the user and sort them
   using the quick sort algorithm. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
void display(int *p, int n);
void swap(int *a, int *b);
int *partition(int *low, int *high);
void quick_sort(int *low, int *high);

int main()
{
	int n;
	printf("give n:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int *p = malloc(n * sizeof(int));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	accept(p, n);
	quick_sort(p, p + n - 1);
	display(p, n);
	free(p);
	return 0;
}

void accept(int *p, int n)
{
	printf("give %d values:\t", n);
	for(int *q = p; q < p + n; q++)
		scanf("%d", q);
}

void display(int *p, int n)
{
	printf("sorted: ");
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
}

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/* last element is the pivot; smaller values go to its left */
int *partition(int *low, int *high)
{
	int pivot = *high;
	int *i = low;				/* next place for a small value */
	for(int *j = low; j < high; j++)
	{
		if(*j <= pivot)
		{
			swap(i, j);
			i++;
		}
	}
	swap(i, high);				/* put pivot in its final place */
	return i;
}

void quick_sort(int *low, int *high)
{
	if(low >= high)
		return;
	int *pi = partition(low, high);
	quick_sort(low, pi - 1);
	quick_sort(pi + 1, high);
}
