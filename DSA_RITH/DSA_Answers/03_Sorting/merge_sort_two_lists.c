/* Day 5 Q3
   Implement a program to accept two lists of elements from the user and sort them
   using the merge sort algorithm. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
void display(int *p, int n);
void merge(int *p1, int n1, int *p2, int n2, int *p3);
void merge_sort(int *p, int n);

int main()
{
	int n1, n2;
	printf("give size of list 1 and list 2:\t");
	scanf("%d %d", &n1, &n2);
	if(n1 <= 0 || n2 <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int *p1 = malloc(n1 * sizeof(int));
	int *p2 = malloc(n2 * sizeof(int));
	int *p3 = malloc((n1 + n2) * sizeof(int));
	if(p1 == NULL || p2 == NULL || p3 == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	printf("list 1: ");
	accept(p1, n1);
	printf("list 2: ");
	accept(p2, n2);

	merge_sort(p1, n1);
	merge_sort(p2, n2);
	printf("sorted list 1:\t");
	display(p1, n1);
	printf("sorted list 2:\t");
	display(p2, n2);

	merge(p1, n1, p2, n2, p3);		/* final merge of the two sorted lists */
	printf("merged list:\t");
	display(p3, n1 + n2);

	free(p1);
	free(p2);
	free(p3);
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

/* merge two sorted arrays p1 (n1) and p2 (n2) into p3 */
void merge(int *p1, int n1, int *p2, int n2, int *p3)
{
	int *a = p1, *b = p2, *c = p3;
	while(a < p1 + n1 && b < p2 + n2)
	{
		if(*a <= *b)			/* <= keeps the sort stable */
			*c++ = *a++;
		else
			*c++ = *b++;
	}
	while(a < p1 + n1)			/* copy whatever is left */
		*c++ = *a++;
	while(b < p2 + n2)
		*c++ = *b++;
}

void merge_sort(int *p, int n)
{
	if(n < 2)
		return;
	int half = n / 2;
	merge_sort(p, half);			/* sort left half */
	merge_sort(p + half, n - half);		/* sort right half */

	int *temp = malloc(n * sizeof(int));
	if(temp == NULL)
	{
		printf("malloc failed");
		return;
	}
	merge(p, half, p + half, n - half, temp);
	for(int *q = p, *t = temp; q < p + n; q++, t++)	/* copy back */
		*q = *t;
	free(temp);
}
