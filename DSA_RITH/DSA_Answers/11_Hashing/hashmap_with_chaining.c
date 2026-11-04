/* Day 9 Q2
   WAP to create a HashMap to store key-value pairs.
   Make sure duplicate values are also allowed to be stored, i.e. on the same hashcode we can
   have multiple values. (Separate chaining: every bucket is a linked list.) */

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define EXIT 0

typedef struct node
{
	int key;
	int value;
	struct node *next;
}node;

/****function declarations****/
int hash_code(int key);
void put(node **table, int key, int value);
void get(node **table, int key);
void remove_key(node **table, int key);
void display(node **table);
void free_table(node **table);

int main()
{
	int choice, key, value;
	node **table = malloc(SIZE * sizeof(node *));	/* array of bucket heads */
	if(table == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	for(node **b = table; b < table + SIZE; b++)
		*b = NULL;

	do
	{
		printf("\n0.exit\n1.put\n2.get\n3.remove key\n4.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give key (not negative) and value:\t");
				scanf("%d %d", &key, &value);
				if(key < 0)
					printf("only keys >= 0\n");
				else
					put(table, key, value);
				break;
			case 2:
				printf("give key:\t");
				scanf("%d", &key);
				get(table, key);
				break;
			case 3:
				printf("give key:\t");
				scanf("%d", &key);
				remove_key(table, key);
				break;
			case 4: display(table); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free_table(table);
	free(table);
	return 0;
}

int hash_code(int key)
{
	return key % SIZE;
}

/* always adds at the start of the bucket's list, so duplicates are kept */
void put(node **table, int key, int value)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	int index = hash_code(key);
	new_node->key = key;
	new_node->value = value;
	new_node->next = *(table + index);
	*(table + index) = new_node;
	printf("(%d, %d) stored in bucket %d\n", key, value, index);
}

void get(node **table, int key)
{
	int found = 0;
	for(node *q = *(table + hash_code(key)); q != NULL; q = q->next)
	{
		if(q->key == key)
		{
			printf("%d -> %d\n", key, q->value);
			found = 1;
		}
	}
	if(found == 0)
		printf("no value for key %d\n", key);
}

/* removes every entry with this key from its bucket */
void remove_key(node **table, int key)
{
	node **head = table + hash_code(key);
	int removed = 0;
	while(*head != NULL)
	{
		if((*head)->key == key)
		{
			node *temp = *head;
			*head = temp->next;		/* unlink, then free */
			free(temp);
			removed++;
		}
		else
			head = &(*head)->next;
	}
	printf("removed %d entries\n", removed);
}

void display(node **table)
{
	for(node **b = table; b < table + SIZE; b++)
	{
		printf("bucket %td: ", b - table);
		for(node *q = *b; q != NULL; q = q->next)
			printf("[%d:%d] -> ", q->key, q->value);
		printf("NULL\n");
	}
}

void free_table(node **table)
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
