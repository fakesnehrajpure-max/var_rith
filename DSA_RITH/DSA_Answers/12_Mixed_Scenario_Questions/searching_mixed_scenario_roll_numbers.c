/* SEARCHING - MIXED SCENARIO
   A class register stores roll numbers in sorted order (duplicates allowed because of a data-entry bug).
   1) Using binary search, find the FIRST and LAST position of a roll number and how many times it appears.
   2) Find the first roll number that is >= a given value (lower bound).
   3) Compare: how many comparisons did linear search take vs binary search? */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
int *first_pos(int *p, int n, int value, int *comps);
int *last_pos(int *p, int n, int value, int *comps);
void linear_comps(int *p, int n, int value);
void lower_bound(int *p, int n, int value);

int main()
{
	int n, value, comps = 0;
	printf("give number of roll numbers:\t");
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

	printf("give roll number to find:\t");
	scanf("%d", &value);
	int *first = first_pos(p, n, value, &comps);
	int *last = last_pos(p, n, value, &comps);
	if(first == NULL)
		printf("%d not present\n", value);
	else
		printf("first %td, last %td, count %td\n", first - p, last - p, last - first + 1);
	printf("binary search comparisons (both ends): %d\n", comps);
	linear_comps(p, n, value);

	printf("give value for lower bound:\t");
	scanf("%d", &value);
	lower_bound(p, n, value);

	free(p);
	return 0;
}

void accept(int *p, int n)
{
	printf("give %d sorted roll numbers:\t", n);
	for(int *q = p; q < p + n; q++)
		scanf("%d", q);
}

/* on a match, remember it and keep searching LEFT */
int *first_pos(int *p, int n, int value, int *comps)
{
	int *low = p, *high = p + n - 1, *mid, *ans = NULL;
	while(low <= high)
	{
		mid = low + (high - low) / 2;
		(*comps)++;
		if(*mid == value)
		{
			ans = mid;
			high = mid - 1;
		}
		else if(*mid < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return ans;
}

/* on a match, remember it and keep searching RIGHT */
int *last_pos(int *p, int n, int value, int *comps)
{
	int *low = p, *high = p + n - 1, *mid, *ans = NULL;
	while(low <= high)
	{
		mid = low + (high - low) / 2;
		(*comps)++;
		if(*mid == value)
		{
			ans = mid;
			low = mid + 1;
		}
		else if(*mid < value)
			low = mid + 1;
		else
			high = mid - 1;
	}
	return ans;
}

void linear_comps(int *p, int n, int value)
{
	int comps = 0;
	for(int *q = p; q < p + n; q++)
	{
		comps++;
		if(*q == value)
			break;
	}
	printf("linear search comparisons: %d\n", comps);
}

void lower_bound(int *p, int n, int value)
{
	int *low = p, *high = p + n, *mid;	/* high is one past the end */
	while(low < high)
	{
		mid = low + (high - low) / 2;
		if(*mid < value)
			low = mid + 1;
		else
			high = mid;
	}
	if(low == p + n)
		printf("no roll number >= %d\n", value);
	else
		printf("first roll >= %d is %d at index %td\n", value, *low, low - p);
}
