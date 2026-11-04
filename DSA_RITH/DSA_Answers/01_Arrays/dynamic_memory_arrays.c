/* Assignment 1 (DS) Q3
   Write a C program which allocates and deallocates memory dynamically.
   (a) Allocate a 1D array dynamically and access the elements
   (b) Allocate a 2D array dynamically
       (1) contiguous rows with fixed no. of cols
       (2) non-contiguous rows with variable no. of columns
   (c) Allocate memory for an array of structure variables dynamically and access
       members of each element */

#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int roll;
	float marks;
}STUDENT;

/****function declarations****/
int one_d(void);
int two_d_contiguous(void);
int two_d_jagged(void);
int struct_array(void);

int main()
{
	if(one_d() == 1) return 1;
	if(two_d_contiguous() == 1) return 1;
	if(two_d_jagged() == 1) return 1;
	if(struct_array() == 1) return 1;
	return 0;
}

int one_d(void)
{
	int n;
	printf("\n(a) 1D size:\t");
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
	for(int *q = p; q < p + n; q++)
		*q = (q - p + 1) * 10;
	printf("1D: ");
	for(int *q = p; q < p + n; q++)
		printf("%d\t", *q);
	printf("\n");
	free(p);
	return 0;
}

int two_d_contiguous(void)
{
	int r, c;
	printf("\n(b1) rows and cols:\t");
	scanf("%d %d", &r, &c);
	if(r <= 0 || c <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int *block = malloc(r * c * sizeof(int));	/* one block for all values */
	int **m = malloc(r * sizeof(int *));		/* row pointers into that block */
	if(block == NULL || m == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	for(int i = 0; i < r; i++)
		m[i] = block + i * c;
	for(int i = 0; i < r; i++)
		for(int j = 0; j < c; j++)
			m[i][j] = i * c + j;
	printf("2D contiguous:\n");
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
			printf("%d\t", m[i][j]);
		printf("\n");
	}
	free(m);
	free(block);
	return 0;
}

int two_d_jagged(void)
{
	int r;
	printf("\n(b2) jagged rows:\t");
	scanf("%d", &r);
	if(r <= 0)
	{
		printf("invalid size\n");
		return 1;
	}
	int **jag = malloc(r * sizeof(int *));
	int *cols = malloc(r * sizeof(int));
	if(jag == NULL || cols == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	for(int i = 0; i < r; i++)
	{
		printf("columns in row %d:\t", i);
		scanf("%d", cols + i);
		jag[i] = malloc(*(cols + i) * sizeof(int));	/* each row is its own block */
		if(jag[i] == NULL)
		{
			printf("malloc failed");
			return 1;
		}
		for(int j = 0; j < *(cols + i); j++)
			jag[i][j] = j + 1;
	}
	printf("2D jagged:\n");
	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < *(cols + i); j++)
			printf("%d\t", jag[i][j]);
		printf("\n");
	}
	for(int i = 0; i < r; i++)
		free(jag[i]);
	free(jag);
	free(cols);
	return 0;
}

int struct_array(void)
{
	int n;
	printf("\n(c) number of students:\t");
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
	for(STUDENT *q = p; q < p + n; q++)
	{
		printf("roll marks:\t");
		scanf("%d %f", &q->roll, &q->marks);
	}
	for(STUDENT *q = p; q < p + n; q++)
		printf("roll %d -> %.2f\n", q->roll, q->marks);
	free(p);
	return 0;
}
