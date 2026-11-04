/* ARRAYS - MIXED SCENARIO
   A temperature sensor logs one reading per minute for N minutes.
   1) Find the hottest and coldest minute.
   2) Find the longest run of minutes where the temperature kept rising.
   3) Rotate the array left by K so the log starts from minute K.
   4) Remove every reading above a limit (sensor glitches) in place, keeping order. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void accept(int *p, int n);
void display(int *p, int n);
void hottest_coldest(int *p, int n);
void longest_rising(int *p, int n);
int rotate_left(int *p, int n, int k);
void remove_glitches(int *p, int *n, int limit);

int main()
{
	int n, k, limit;
	printf("give number of readings:\t");
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
	hottest_coldest(p, n);
	longest_rising(p, n);

	printf("give K to rotate left:\t");
	scanf("%d", &k);
	if(rotate_left(p, n, k) == 1)
		return 1;

	printf("give glitch limit:\t");
	scanf("%d", &limit);
	remove_glitches(p, &n, limit);

	free(p);
	return 0;
}

void accept(int *p, int n)
{
	printf("give %d readings:\t", n);
	for(int *q = p; q < p + n; q++)
		scanf("%d", q);
}

void display(int *p, int n)
{
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
}

void hottest_coldest(int *p, int n)
{
	int *hot = p, *cold = p;
	for(int *q = p + 1; q < p + n; q++)
	{
		if(*q > *hot)
			hot = q;
		if(*q < *cold)
			cold = q;
	}
	printf("hottest minute %td (%d), coldest minute %td (%d)\n", hot - p, *hot, cold - p, *cold);
}

void longest_rising(int *p, int n)
{
	int best = 1, current = 1;
	for(int *q = p + 1; q < p + n; q++)
	{
		if(*q > *(q - 1))
			current++;
		else
			current = 1;
		if(current > best)
			best = current;
	}
	printf("longest rising run: %d minutes\n", best);
}

int rotate_left(int *p, int n, int k)
{
	k = k % n;
	int *temp = malloc(n * sizeof(int));
	if(temp == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	for(int *q = temp; q < temp + n; q++)
		*q = *(p + ((q - temp) + k) % n);	/* new position i takes old (i + k) % n */
	printf("rotated: ");
	display(temp, n);
	free(temp);
	return 0;
}

/* two pointers: r reads every value, w writes only the good ones */
void remove_glitches(int *p, int *n, int limit)
{
	int *w = p;
	for(int *r = p; r < p + *n; r++)
	{
		if(*r <= limit)
		{
			*w = *r;
			w++;
		}
	}
	*n = w - p;
	printf("cleaned (%d left): ", *n);
	display(p, *n);
}
