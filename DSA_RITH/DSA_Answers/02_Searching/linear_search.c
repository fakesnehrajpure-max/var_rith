/* Assignment 2 (DS) Q1
   Write a C program to implement Linear Search. Check for duplicate inputs: if duplicate
   elements are allowed, linear search must report them accordingly. Apply an appropriate
   condition check for the element-not-found scenario.
   (a) Search element (iterative)           (b) Search element (recursion)
   (c) Print input array (iterative)        (d) Print input array (recursion)
   (e) Print array in reverse (iterative)   (f) Print array in reverse (recursion) */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

/****function declarations****/
void accept(int *p, int n);
void search_iter(int *p, int n, int value);
int search_rec(int *p, int n, int value, int *start);
void print_iter(int *p, int n);
void print_rec(int *p, int n);
void reverse_iter(int *p, int n);
void reverse_rec(int *p, int n);

int main()
{
	int n, choice, value;
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

	do
	{
		printf("\n0.exit\n1.search iterative\n2.search recursive\n3.print iterative\n");
		printf("4.print recursive\n5.reverse iterative\n6.reverse recursive\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				search_iter(p, n, value);
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				if(search_rec(p, n, value, p) == 0)
					printf("%d not found\n", value);
				break;
			case 3: print_iter(p, n); break;
			case 4: print_rec(p, n); printf("\n"); break;
			case 5: reverse_iter(p, n); break;
			case 6: reverse_rec(p, n); printf("\n"); break;
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

void search_iter(int *p, int n, int value)
{
	int found = 0;
	for(int *q = p; q < p + n; q++)
	{
		if(*q == value)
		{
			printf("%d found at index %td\n", value, q - p);	/* every duplicate is reported */
			found++;
		}
	}
	if(found == 0)
		printf("%d not found\n", value);
}

/* returns how many matches; start is the array base, used only to print the index */
int search_rec(int *p, int n, int value, int *start)
{
	if(n == 0)
		return 0;
	int here = 0;
	if(*p == value)
	{
		printf("%d found at index %td\n", value, p - start);
		here = 1;
	}
	return here + search_rec(p + 1, n - 1, value, start);
}

void print_iter(int *p, int n)
{
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
}

void print_rec(int *p, int n)
{
	if(n == 0)
		return;
	printf("%d\t", *p);
	print_rec(p + 1, n - 1);
}

void reverse_iter(int *p, int n)
{
	for(int *q = p + n - 1; q >= p; q--)
		printf("%d\t", *q);
	printf("\n");
}

void reverse_rec(int *p, int n)
{
	if(n == 0)
		return;
	reverse_rec(p + 1, n - 1);		/* recurse first, then print = reverse order */
	printf("%d\t", *p);
}
