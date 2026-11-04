/* SORTING - MIXED SCENARIO
   Exam results: each student has a name and marks.
   1) Rank students by marks (highest first). Students with equal marks must keep their
      original order (needs a STABLE sort -> use merge sort; quick sort is unsafe here).
   2) Print the top 3 using a max-heap without sorting everything.
   3) Count how many swaps bubble sort would need on the marks (measure of disorder). */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	char name[30];
	int marks;
}STUDENT;

/****function declarations****/
void accept(STUDENT *p, int n);
void bubble_swaps(STUDENT *p, int n);
void heapify(int *h, int n, int i);
void top_three(STUDENT *p, int n);
void merge_desc(STUDENT *p1, int n1, STUDENT *p2, int n2, STUDENT *p3);
void merge_sort_desc(STUDENT *p, int n);
void display(STUDENT *p, int n);

int main()
{
	int n;
	printf("give number of students:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	STUDENT *p = malloc(n * sizeof(STUDENT));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	accept(p, n);
	bubble_swaps(p, n);
	top_three(p, n);
	merge_sort_desc(p, n);
	display(p, n);
	printf("quick sort is not stable, so two students with the same marks could swap order\n");
	free(p);
	return 0;
}

void accept(STUDENT *p, int n)
{
	for(STUDENT *q = p; q < p + n; q++)
	{
		printf("name marks:\t");
		scanf("%29s %d", q->name, &q->marks);
	}
}

/* counts swaps on a copy of the marks, so the original order is untouched */
void bubble_swaps(STUDENT *p, int n)
{
	int swaps = 0, temp;
	int *m = malloc(n * sizeof(int));
	if(m == NULL)
	{
		printf("malloc failed");
		return;
	}
	for(int *q = m; q < m + n; q++)
		*q = (p + (q - m))->marks;
	for(int *end = m + n - 1; end > m; end--)
	{
		for(int *q = m; q < end; q++)
		{
			if(*q > *(q + 1))
			{
				temp = *q;
				*q = *(q + 1);
				*(q + 1) = temp;
				swaps++;
			}
		}
	}
	printf("bubble sort swaps needed: %d\n", swaps);
	free(m);
}

void heapify(int *h, int n, int i)
{
	int largest = i, left = 2 * i + 1, right = 2 * i + 2, temp;
	if(left < n && *(h + left) > *(h + largest))
		largest = left;
	if(right < n && *(h + right) > *(h + largest))
		largest = right;
	if(largest != i)
	{
		temp = *(h + i);
		*(h + i) = *(h + largest);
		*(h + largest) = temp;
		heapify(h, n, largest);
	}
}

void top_three(STUDENT *p, int n)
{
	int *h = malloc(n * sizeof(int));
	if(h == NULL)
	{
		printf("malloc failed");
		return;
	}
	for(int *q = h; q < h + n; q++)
		*q = (p + (q - h))->marks;
	for(int i = n / 2 - 1; i >= 0; i--)	/* build max heap */
		heapify(h, n, i);
	int size = n;
	printf("top 3 marks (heap): ");
	for(int k = 0; k < 3 && size > 0; k++)
	{
		printf("%d ", *h);		/* root is the biggest */
		*h = *(h + size - 1);		/* move last to root, shrink, fix */
		size--;
		heapify(h, size, 0);
	}
	printf("\n");
	free(h);
}

void merge_desc(STUDENT *p1, int n1, STUDENT *p2, int n2, STUDENT *p3)
{
	STUDENT *a = p1, *b = p2, *c = p3;
	while(a < p1 + n1 && b < p2 + n2)
	{
		if(a->marks >= b->marks)	/* >= takes the left one on a tie: stable */
			*c++ = *a++;
		else
			*c++ = *b++;
	}
	while(a < p1 + n1)
		*c++ = *a++;
	while(b < p2 + n2)
		*c++ = *b++;
}

void merge_sort_desc(STUDENT *p, int n)
{
	if(n < 2)
		return;
	int half = n / 2;
	merge_sort_desc(p, half);
	merge_sort_desc(p + half, n - half);
	STUDENT *temp = malloc(n * sizeof(STUDENT));
	if(temp == NULL)
	{
		printf("malloc failed");
		return;
	}
	merge_desc(p, half, p + half, n - half, temp);
	for(STUDENT *q = p, *t = temp; q < p + n; q++, t++)
		*q = *t;
	free(temp);
}

void display(STUDENT *p, int n)
{
	printf("rank list (stable):\n");
	for(STUDENT *q = p; q < p + n; q++)
		printf("%td. %s %d\n", q - p + 1, q->name, q->marks);
}
