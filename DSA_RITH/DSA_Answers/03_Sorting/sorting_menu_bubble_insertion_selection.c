/* Day 4 Q1
   Write a menu driven program consisting of multiple sort methods.
   Accept the length of the array from the user at runtime. Allocate memory for the array at runtime.
   Using accept() get values for the array from the user. display() must print values on the terminal.
   Using switch case ask the user which sort method he wants to use.
   Implement bubble sort, insertion sort and selection sort using functions. */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

/****function declarations****/
void accept(int *p, int n);
void display(int *p, int n);
void bubble_sort(int *p, int n);
void insertion_sort(int *p, int n);
void selection_sort(int *p, int n);

int main()
{
	int n, choice;
	printf("give length of array:\t");
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

	do
	{
		printf("\n0.exit\n1.bubble sort\n2.insertion sort\n3.selection sort\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: accept(p, n); bubble_sort(p, n); display(p, n); break;
			case 2: accept(p, n); insertion_sort(p, n); display(p, n); break;
			case 3: accept(p, n); selection_sort(p, n); display(p, n); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

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

void bubble_sort(int *p, int n)
{
	int temp, swapped;
	for(int *end = p + n - 1; end > p; end--)	/* after each pass the biggest sits at end */
	{
		swapped = 0;
		for(int *q = p; q < end; q++)
		{
			if(*q > *(q + 1))
			{
				temp = *q;
				*q = *(q + 1);
				*(q + 1) = temp;
				swapped = 1;
			}
		}
		if(swapped == 0)			/* no swap in a pass: already sorted */
			break;
	}
}

void insertion_sort(int *p, int n)
{
	int key;
	int *r;
	for(int *q = p + 1; q < p + n; q++)
	{
		key = *q;
		r = q - 1;
		while(r >= p && *r > key)		/* shift bigger values right */
		{
			*(r + 1) = *r;
			r--;
		}
		*(r + 1) = key;
	}
}

void selection_sort(int *p, int n)
{
	int temp;
	int *min;
	for(int *q = p; q < p + n - 1; q++)
	{
		min = q;
		for(int *r = q + 1; r < p + n; r++)	/* find the smallest in the rest */
		{
			if(*r < *min)
				min = r;
		}
		temp = *q;
		*q = *min;
		*min = temp;
	}
}
