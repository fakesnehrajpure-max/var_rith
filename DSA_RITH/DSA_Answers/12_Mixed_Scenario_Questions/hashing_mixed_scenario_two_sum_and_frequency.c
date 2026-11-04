/* HASHING - MIXED SCENARIO
   A shop records the price of every item sold today.
   1) Using your own hash table (chaining), count how many times each price was sold.
   2) Find the first price that was sold exactly once.
   3) A customer has a gift card of value T: find two different items whose prices add up to T
      in O(n) using the hash table (two-sum). */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 11

typedef struct node
{
	int key;
	int count;
	struct node *next;
}node;

/****function declarations****/
int hash_code(int key);
node *searchNode(node **table, int key);
void add(node **table, int key);
void show_frequency(node **table);
void first_unique(node **table, int *p, int n);
void two_sum(node **table, int *p, int n, int target);
void clear(node **table);

int main()
{
	int n, target;
	node *table[SIZE];
	for(node **b = table; b < table + SIZE; b++)
		*b = NULL;

	printf("give number of items sold:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid count\n");
		return 1;
	}
	int *p = malloc(n * sizeof(int));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	printf("give %d prices (not negative):\t", n);
	for(int *q = p; q < p + n; q++)
	{
		scanf("%d", q);
		add(table, *q);
	}
	show_frequency(table);
	first_unique(table, p, n);
	clear(table);

	printf("give gift card value:\t");
	scanf("%d", &target);
	two_sum(table, p, n, target);
	clear(table);

	free(p);
	return 0;
}

int hash_code(int key)
{
	return key % SIZE;
}

node *searchNode(node **table, int key)
{
	if(key < 0)
		return NULL;
	for(node *q = *(table + hash_code(key)); q != NULL; q = q->next)
	{
		if(q->key == key)
			return q;
	}
	return NULL;
}

/* seen before: count++, else add a new node at the bucket's head */
void add(node **table, int key)
{
	node *found = searchNode(table, key);
	if(found != NULL)
	{
		found->count++;
		return;
	}
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	int index = hash_code(key);
	new_node->key = key;
	new_node->count = 1;
	new_node->next = *(table + index);
	*(table + index) = new_node;
}

void show_frequency(node **table)
{
	printf("frequency:\n");
	for(node **b = table; b < table + SIZE; b++)
	{
		for(node *q = *b; q != NULL; q = q->next)
			printf("  price %d sold %d time(s)\n", q->key, q->count);
	}
}

/* walk the prices in their original order, check each count in the table */
void first_unique(node **table, int *p, int n)
{
	for(int *q = p; q < p + n; q++)
	{
		if(searchNode(table, *q)->count == 1)
		{
			printf("first price sold once: %d\n", *q);
			return;
		}
	}
	printf("no price sold exactly once\n");
}

/* for each price, is (target - price) already in the table? add after checking */
void two_sum(node **table, int *p, int n, int target)
{
	for(int *q = p; q < p + n; q++)
	{
		if(searchNode(table, target - *q) != NULL)
		{
			printf("buy items priced %d and %d\n", target - *q, *q);
			return;
		}
		add(table, *q);
	}
	printf("no pair adds up to %d\n", target);
}

void clear(node **table)
{
	node *temp;
	for(node **b = table; b < table + SIZE; b++)
	{
		while(*b != NULL)
		{
			temp = *b;
			*b = temp->next;
			free(temp);
		}
	}
}
