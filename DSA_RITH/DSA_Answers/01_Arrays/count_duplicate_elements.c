/* Assignment 2 (DS) Q4: Count Duplicate Elements
   Given an integer array, numbers, count the number of elements that occur more than once.
   Example: numbers = [1, 3, 3, 4, 4, 4]. There are two non-unique elements: 3 and 4.
   countDuplicate(int numbers[n]) returns the number of non-unique values. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
void countDuplicate(int *p, int n);

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
	countDuplicate(p, n);
	free(p);
	return 0;
}

void accept(int *p, int n)
{
	printf("give %d values:\t", n);
	for(int *q = p; q < p + n; q++)
		scanf("%d", q);
}

void countDuplicate(int *p, int n)
{
	int result = 0, seen_before, repeats;
	for(int *q = p; q < p + n; q++)
	{
		seen_before = 0;
		for(int *r = p; r < q; r++)		/* was this value already counted? */
		{
			if(*r == *q)
			{
				seen_before = 1;
				break;
			}
		}
		if(seen_before == 1)
			continue;

		repeats = 0;
		for(int *r = q + 1; r < p + n; r++)	/* does it appear again later? */
		{
			if(*r == *q)
			{
				repeats = 1;
				break;
			}
		}
		if(repeats == 1)
			result++;
	}
	printf("non-unique values = %d\n", result);
}
