/* Day 7 Q2
   Take a list of unsorted elements and heap sort them using the heapify technique. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
void display(int *p, int n);
void swap(int *a, int *b);
void heapify(int *p, int n, int i);
void heap_sort(int *p, int n);

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
	heap_sort(p, n);
	printf("sorted:   ");
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

/* children of index i are 2i+1 and 2i+2 */
void heapify(int *p, int n, int i)
{
	int largest = i, left = 2 * i + 1, right = 2 * i + 2;
	if(left < n && *(p + left) > *(p + largest))
		largest = left;
	if(right < n && *(p + right) > *(p + largest))
		largest = right;
	if(largest != i)
	{
		swap(p + i, p + largest);
		heapify(p, n, largest);		/* fix the subtree we disturbed */
	}
}

void heap_sort(int *p, int n)
{
	for(int i = n / 2 - 1; i >= 0; i--)	/* build max heap bottom-up */
		heapify(p, n, i);
	printf("max heap: ");
	display(p, n);

	for(int end = n - 1; end > 0; end--)
	{
		swap(p, p + end);		/* biggest goes to the end */
		heapify(p, end, 0);		/* fix the smaller heap */
	}
}
