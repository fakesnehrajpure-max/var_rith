/* Day 10 (sample exam question)
   Implement a singly linked list of employees to store employee details (emp_id, ename, e_salary).
   a. Add new employee record in LL in appropriate position as per emp_id.
   b. Display all employees in sorted order (Note: don't use any sorting).
   c. Find and display employee details with highest salary.
   In the same program create another LL for project_id and emp_id to store details of which
   project is assigned to an employee.
   At last display project-wise employee details. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXIT 0

typedef struct emp
{
	int emp_id;
	char ename[30];
	float salary;
	struct emp *next;
}emp;

typedef struct proj
{
	int project_id;
	int emp_id;			/* link to the employee list */
	struct proj *next;
}proj;

/****function declarations****/
emp *createEmp(int id, char *name, float salary);
void add_employee(emp **ehead, int id, char *name, float salary);
void display_employees(emp *ehead);
void highest_salary(emp *ehead);
emp *search_employee(emp *ehead, int id);
void add_project(proj **phead, emp *ehead, int project_id, int emp_id);
void project_wise(proj *phead, emp *ehead);
void free_lists(emp **ehead, proj **phead);

int main()
{
	emp *ehead = NULL;
	proj *phead = NULL;
	int choice, id, project_id;
	char name[30];
	float salary;

	do
	{
		printf("\n0.exit\n1.add employee\n2.display employees\n3.highest salary\n");
		printf("4.assign project\n5.project-wise display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give emp_id name salary:\t");
				scanf("%d %29s %f", &id, name, &salary);
				add_employee(&ehead, id, name, salary);
				break;
			case 2: display_employees(ehead); break;
			case 3: highest_salary(ehead); break;
			case 4:
				printf("give project_id emp_id:\t");
				scanf("%d %d", &project_id, &id);
				add_project(&phead, ehead, project_id, id);
				break;
			case 5: project_wise(phead, ehead); break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free_lists(&ehead, &phead);
	return 0;
}

emp *createEmp(int id, char *name, float salary)
{
	emp *new_node = malloc(sizeof(emp));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return NULL;
	}
	new_node->emp_id = id;
	strcpy(new_node->ename, name);
	new_node->salary = salary;
	new_node->next = NULL;
	return new_node;
}

/* (a) sorted insert by emp_id, so the list is always in order */
void add_employee(emp **ehead, int id, char *name, float salary)
{
	if(search_employee(*ehead, id) != NULL)
	{
		printf("emp_id %d already exists\n", id);
		return;
	}
	emp *new_node = createEmp(id, name, salary);
	if(new_node == NULL)
		return;

	if(*ehead == NULL || id < (*ehead)->emp_id)	/* goes first */
	{
		new_node->next = *ehead;
		*ehead = new_node;
		return;
	}
	emp *q = *ehead;
	while(q->next != NULL && q->next->emp_id < id)	/* stop before the bigger id */
		q = q->next;
	new_node->next = q->next;			/* connect first, then link */
	q->next = new_node;
}

/* (b) already sorted, so a plain walk prints it in order */
void display_employees(emp *ehead)
{
	if(ehead == NULL)
	{
		printf("no employees\n");
		return;
	}
	printf("emp_id\tname\tsalary\n");
	for(emp *q = ehead; q != NULL; q = q->next)
		printf("%d\t%s\t%.2f\n", q->emp_id, q->ename, q->salary);
}

/* (c) walk and remember the node with the biggest salary */
void highest_salary(emp *ehead)
{
	if(ehead == NULL)
	{
		printf("no employees\n");
		return;
	}
	emp *max = ehead;
	for(emp *q = ehead->next; q != NULL; q = q->next)
	{
		if(q->salary > max->salary)
			max = q;
	}
	printf("highest salary: %d %s %.2f\n", max->emp_id, max->ename, max->salary);
}

emp *search_employee(emp *ehead, int id)
{
	for(emp *q = ehead; q != NULL; q = q->next)
	{
		if(q->emp_id == id)
			return q;
	}
	return NULL;
}

/* project list kept sorted by project_id, so the same projects come together */
void add_project(proj **phead, emp *ehead, int project_id, int emp_id)
{
	if(search_employee(ehead, emp_id) == NULL)
	{
		printf("emp_id %d does not exist\n", emp_id);
		return;
	}
	proj *new_node = malloc(sizeof(proj));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return;
	}
	new_node->project_id = project_id;
	new_node->emp_id = emp_id;
	new_node->next = NULL;

	if(*phead == NULL || project_id < (*phead)->project_id)
	{
		new_node->next = *phead;
		*phead = new_node;
		return;
	}
	proj *q = *phead;
	while(q->next != NULL && q->next->project_id <= project_id)
		q = q->next;
	new_node->next = q->next;
	q->next = new_node;
}

/* walk the project list; for each node, look up the employee by emp_id */
void project_wise(proj *phead, emp *ehead)
{
	if(phead == NULL)
	{
		printf("no projects assigned\n");
		return;
	}
	int current = -1;
	emp *e;
	for(proj *q = phead; q != NULL; q = q->next)
	{
		if(q->project_id != current)		/* new project heading */
		{
			current = q->project_id;
			printf("project %d:\n", current);
		}
		e = search_employee(ehead, q->emp_id);
		if(e != NULL)
			printf("\t%d\t%s\t%.2f\n", e->emp_id, e->ename, e->salary);
	}
}

void free_lists(emp **ehead, proj **phead)
{
	emp *etemp;
	proj *ptemp;
	while(*ehead != NULL)
	{
		etemp = *ehead;
		*ehead = etemp->next;
		free(etemp);
	}
	while(*phead != NULL)
	{
		ptemp = *phead;
		*phead = ptemp->next;
		free(ptemp);
	}
}
