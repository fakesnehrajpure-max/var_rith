/* Assignment 1 (DS) Q1
   Write a C program that declares an array of length N containing integers
   between 1 and N. Implement a menu driven program using switch case for:
   (a) insert element at index        (b) delete element at index
   (c) find min value                 (d) find max value
   (e) display array elements         (f) reverse display array elements
   (g) search element in array        (h) array element count
   (i) average of all array elements  (j) determine if array contains any duplicates
   (k) reverse array elements */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

/****function declarations****/
void insert_at(int *p, int *n, int N, int index, int value);
void delete_at(int *p, int *n, int index);
void find_min(int *p, int n);
void find_max(int *p, int n);
void display(int *p, int n);
void reverse_display(int *p, int n);
void search(int *p, int n, int value);
void average(int *p, int n);
void duplicates(int *p, int n);
void reverse_array(int *p, int n);

int main()
{
	int N, n = 0, choice, index, value;

	printf("give N (array length):\t");
	scanf("%d", &N);
	if(N <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int *p = malloc(N * sizeof(int));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}

	do
	{
		printf("\n0.exit\n1.insert at index\n2.delete at index\n3.min\n4.max\n5.display\n6.reverse display\n");
		printf("7.search\n8.count\n9.average\n10.duplicates\n11.reverse array\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give index and value:\t");
				scanf("%d %d", &index, &value);
				insert_at(p, &n, N, index, value);
				break;
			case 2:
				printf("give index:\t");
				scanf("%d", &index);
				delete_at(p, &n, index);
				break;
			case 3: find_min(p, n); break;
			case 4: find_max(p, n); break;
			case 5: display(p, n); break;
			case 6: reverse_display(p, n); break;
			case 7:
				printf("give value to search:\t");
				scanf("%d", &value);
				search(p, n, value);
				break;
			case 8: printf("count = %d\n", n); break;
			case 9: average(p, n); break;
			case 10: duplicates(p, n); break;
			case 11: reverse_array(p, n); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free(p);
	return 0;
}

void insert_at(int *p, int *n, int N, int index, int value)
{
	if(*n == N)
	{
		printf("array is full\n");
		return;
	}
	if(index < 0 || index > *n)
	{
		printf("invalid index\n");
		return;
	}
	if(value < 1 || value > N)
	{
		printf("value must be between 1 and %d\n", N);
		return;
	}
	for(int *q = p + *n; q > p + index; q--)	/* shift right, starting from the end */
		*q = *(q - 1);
	*(p + index) = value;
	(*n)++;
}

void delete_at(int *p, int *n, int index)
{
	if(index < 0 || index >= *n)
	{
		printf("invalid index\n");
		return;
	}
	for(int *q = p + index; q < p + *n - 1; q++)	/* shift left */
		*q = *(q + 1);
	(*n)--;
}

void find_min(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	int *min = p;
	for(int *q = p + 1; q < p + n; q++)
	{
		if(*q < *min)
			min = q;
	}
	printf("min = %d at index %td\n", *min, min - p);
}

void find_max(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	int *max = p;
	for(int *q = p + 1; q < p + n; q++)
	{
		if(*q > *max)
			max = q;
	}
	printf("max = %d at index %td\n", *max, max - p);
}

void display(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
}

void reverse_display(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	for(int *q = p + n - 1; q >= p; q--)
		printf("%d\t", *q);
	printf("\n");
}

void search(int *p, int n, int value)
{
	int found = 0;
	for(int *q = p; q < p + n; q++)
	{
		if(*q == value)
		{
			printf("%d found at index %td\n", value, q - p);
			found = 1;
		}
	}
	if(found == 0)
		printf("%d not found\n", value);
}

void average(int *p, int n)
{
	if(n == 0)
	{
		printf("array is empty\n");
		return;
	}
	int sum = 0;
	for(int *q = p; q < p + n; q++)
		sum = sum + *q;
	printf("average = %.2f\n", (float)sum / n);
}

void duplicates(int *p, int n)
{
	for(int *q = p; q < p + n; q++)
	{
		for(int *r = q + 1; r < p + n; r++)
		{
			if(*q == *r)
			{
				printf("array has duplicates (%d)\n", *q);
				return;
			}
		}
	}
	printf("no duplicates\n");
}

void reverse_array(int *p, int n)
{
	int *start = p, *end = p + n - 1, temp;
	while(start < end)				/* two-pointer swap */
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
	display(p, n);
}
