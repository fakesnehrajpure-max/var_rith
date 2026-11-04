/* Assignment 2 (DS) Q3: Find the Factor
   Determine the factors of a number (all positive integers that evenly divide it) and
   return the pth element of the list, sorted ascending. If there is no pth element, return 0.
   Example: n = 20 and p = 3. Factors of 20 = {1, 2, 4, 5, 10, 20}, so 4 is returned.
   If p > 6, 0 would be returned. */

#include <stdio.h>
#include <stdlib.h>

/****function declarations****/
void pthFactor(int n, int p);

int main()
{
	int n, p;
	printf("give n and p:\t");
	scanf("%d %d", &n, &p);
	if(n <= 0 || p <= 0)
	{
		printf("n and p must be positive\n");
		return 1;
	}
	pthFactor(n, p);
	return 0;
}

void pthFactor(int n, int p)
{
	int count = 0;
	for(int i = 1; i <= n; i++)
	{
		if(n % i == 0)
		{
			count++;
			if(count == p)
			{
				printf("pth factor = %d\n", i);
				return;
			}
		}
	}
	printf("pth factor = 0 (only %d factors)\n", count);
}
