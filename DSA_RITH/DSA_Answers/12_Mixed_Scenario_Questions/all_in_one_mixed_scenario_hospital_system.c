/* ALL-IN-ONE MIXED SCENARIO (uses several data structures together)
   Hospital emergency system:
   - Patients register with ID, name and severity (1-10). Store them in a HASH TABLE by ID for O(1) lookup.
   - Waiting patients go into a MAX-HEAP by severity so the most serious is treated first.
   - Every treated patient is pushed onto a STACK so the doctor can "undo" the last treatment record.
   - Every registration is also appended to a SINGLY LINKED LIST as the day's log, printed at the end.
   Menu: Register, Treat next, Undo last treatment, Find patient by ID, Show waiting, Show day log. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUCKETS 13
#define MAX 100
#define EXIT 0

typedef struct
{
	int id;
	char name[30];
	int severity;
	int treated;
}PATIENT;

typedef struct hnode			/* hash table chain node */
{
	PATIENT *p;
	struct hnode *next;
}hnode;

typedef struct lnode			/* day log list node */
{
	PATIENT *p;
	struct lnode *next;
}lnode;

typedef struct
{
	PATIENT *heap[MAX];
	int size;
}HEAP;

typedef struct
{
	PATIENT *stack[MAX];
	int top;
}STACK;

/****function declarations****/
int hash_code(int id);
void ht_put(hnode **table, PATIENT *p);
PATIENT *ht_get(hnode **table, int id);
void swap(PATIENT **a, PATIENT **b);
void heap_push(HEAP *h, PATIENT *p);
PATIENT *heap_pop(HEAP *h);
void log_add(lnode **head, lnode **tail, PATIENT *p);
void register_patient(hnode **table, HEAP *h, lnode **head, lnode **tail);
void treat_next(HEAP *h, STACK *s);
void undo_treatment(HEAP *h, STACK *s);
void find_patient(hnode **table);
void show_waiting(HEAP *h);
void show_log(lnode *head);
void free_all(hnode **table, lnode **head);

int main()
{
	hnode *table[BUCKETS];
	HEAP h;
	STACK s;
	lnode *head = NULL, *tail = NULL;
	int choice;

	for(hnode **b = table; b < table + BUCKETS; b++)
		*b = NULL;
	h.size = 0;
	s.top = -1;

	do
	{
		printf("\n0.exit\n1.register\n2.treat next\n3.undo last treatment\n4.find by ID\n");
		printf("5.show waiting\n6.show day log\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1: register_patient(table, &h, &head, &tail); break;
			case 2: treat_next(&h, &s); break;
			case 3: undo_treatment(&h, &s); break;
			case 4: find_patient(table); break;
			case 5: show_waiting(&h); break;
			case 6: show_log(head); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free_all(table, &head);
	return 0;
}

int hash_code(int id)
{
	return id % BUCKETS;
}

void ht_put(hnode **table, PATIENT *p)
{
	hnode *new_node = malloc(sizeof(hnode));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	int index = hash_code(p->id);
	new_node->p = p;
	new_node->next = *(table + index);
	*(table + index) = new_node;
}

PATIENT *ht_get(hnode **table, int id)
{
	if(id < 0)
		return NULL;
	for(hnode *q = *(table + hash_code(id)); q != NULL; q = q->next)
	{
		if(q->p->id == id)
			return q->p;
	}
	return NULL;
}

void swap(PATIENT **a, PATIENT **b)
{
	PATIENT *temp = *a;
	*a = *b;
	*b = temp;
}

/* add at the end, then move up while bigger than the parent */
void heap_push(HEAP *h, PATIENT *p)
{
	if(h->size == MAX)
	{
		printf("heap is full\n");
		return;
	}
	int i = h->size;
	*(h->heap + i) = p;
	h->size++;
	while(i > 0 && (*(h->heap + (i - 1) / 2))->severity < (*(h->heap + i))->severity)
	{
		swap(h->heap + i, h->heap + (i - 1) / 2);
		i = (i - 1) / 2;
	}
}

/* take the root, move the last to the root, then move it down */
PATIENT *heap_pop(HEAP *h)
{
	PATIENT *top = *h->heap;
	h->size--;
	*h->heap = *(h->heap + h->size);
	int i = 0, left, right, largest;
	while(1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		largest = i;
		if(left < h->size && (*(h->heap + left))->severity > (*(h->heap + largest))->severity)
			largest = left;
		if(right < h->size && (*(h->heap + right))->severity > (*(h->heap + largest))->severity)
			largest = right;
		if(largest == i)
			break;
		swap(h->heap + i, h->heap + largest);
		i = largest;
	}
	return top;
}

void log_add(lnode **head, lnode **tail, PATIENT *p)
{
	lnode *new_node = malloc(sizeof(lnode));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	new_node->p = p;
	new_node->next = NULL;
	if(*head == NULL)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
}

void register_patient(hnode **table, HEAP *h, lnode **head, lnode **tail)
{
	int id, severity;
	char name[30];
	printf("give id name severity(1-10):\t");
	scanf("%d %29s %d", &id, name, &severity);
	if(id < 0 || severity < 1 || severity > 10)
	{
		printf("invalid input\n");
		return;
	}
	if(ht_get(table, id) != NULL)
	{
		printf("ID already exists\n");
		return;
	}
	PATIENT *p = malloc(sizeof(PATIENT));
	if(p == NULL)
	{
		printf("malloc failed");
		return;
	}
	p->id = id;
	strcpy(p->name, name);
	p->severity = severity;
	p->treated = 0;
	ht_put(table, p);
	heap_push(h, p);
	log_add(head, tail, p);
}

void treat_next(HEAP *h, STACK *s)
{
	if(h->size == 0)
	{
		printf("no one waiting\n");
		return;
	}
	PATIENT *p = heap_pop(h);
	p->treated = 1;
	s->top++;
	*(s->stack + s->top) = p;
	printf("treating %s (severity %d)\n", p->name, p->severity);
}

void undo_treatment(HEAP *h, STACK *s)
{
	if(s->top == -1)
	{
		printf("nothing to undo\n");
		return;
	}
	PATIENT *p = *(s->stack + s->top);
	s->top--;
	p->treated = 0;
	heap_push(h, p);
	printf("%s put back in the waiting heap\n", p->name);
}

void find_patient(hnode **table)
{
	int id;
	printf("give id:\t");
	scanf("%d", &id);
	PATIENT *p = ht_get(table, id);
	if(p == NULL)
		printf("not found\n");
	else if(p->treated == 1)
		printf("%s, severity %d, treated\n", p->name, p->severity);
	else
		printf("%s, severity %d, waiting\n", p->name, p->severity);
}

void show_waiting(HEAP *h)
{
	if(h->size == 0)
	{
		printf("no one waiting\n");
		return;
	}
	printf("waiting (heap order): ");
	for(PATIENT **q = h->heap; q < h->heap + h->size; q++)
		printf("%s(%d) ", (*q)->name, (*q)->severity);
	printf("\n");
}

void show_log(lnode *head)
{
	for(lnode *q = head; q != NULL; q = q->next)
		printf("%d %s -> ", q->p->id, q->p->name);
	printf("END\n");
}

void free_all(hnode **table, lnode **head)
{
	hnode *htemp;
	lnode *ltemp;
	for(hnode **b = table; b < table + BUCKETS; b++)
	{
		while(*b != NULL)
		{
			htemp = *b;
			*b = htemp->next;
			free(htemp);
		}
	}
	while(*head != NULL)			/* each patient is freed once, from the log */
	{
		ltemp = *head;
		*head = ltemp->next;
		free(ltemp->p);
		free(ltemp);
	}
}
