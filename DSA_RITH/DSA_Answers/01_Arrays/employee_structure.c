/* Assignment 1 (DS) Q2
   Create an employee structure with members empid, employee name, salary, year of joining etc.
   Accept the data for a certain number of employees and find their total, average, max, min salary.
   Also find the employees with maximum and minimum service; use a function to find the
   service of each employee in the array. */

#include <stdio.h>
#include <stdlib.h>
#define CURRENT_YEAR 2026

typedef struct
{
	int empid;
	char name[30];
	float salary;
	int year;
}EMP;

/****function declarations****/
void accept(EMP *p, int n);
int service(EMP *e);
void salary_report(EMP *p, int n);
void service_report(EMP *p, int n);

int main()
{
	int n;
	printf("give number of employees:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid count\n");
		return 1;
	}
	EMP *p = malloc(n * sizeof(EMP));
	if(p == NULL)
	{
		printf("malloc failed");
		return 1;
	}
	accept(p, n);
	salary_report(p, n);
	service_report(p, n);
	free(p);
	return 0;
}

void accept(EMP *p, int n)
{
	for(EMP *q = p; q < p + n; q++)
	{
		printf("employee %td: empid name salary year_of_joining:\t", q - p + 1);
		scanf("%d %29s %f %d", &q->empid, q->name, &q->salary, &q->year);
	}
}

int service(EMP *e)
{
	return CURRENT_YEAR - e->year;
}

void salary_report(EMP *p, int n)
{
	float total = 0;
	EMP *max = p, *min = p;
	for(EMP *q = p; q < p + n; q++)
	{
		total = total + q->salary;
		if(q->salary > max->salary)
			max = q;
		if(q->salary < min->salary)
			min = q;
	}
	printf("total salary   = %.2f\n", total);
	printf("average salary = %.2f\n", total / n);
	printf("max salary     = %.2f (%s)\n", max->salary, max->name);
	printf("min salary     = %.2f (%s)\n", min->salary, min->name);
}

void service_report(EMP *p, int n)
{
	EMP *max = p, *min = p;
	for(EMP *q = p; q < p + n; q++)
	{
		if(service(q) > service(max))
			max = q;
		if(service(q) < service(min))
			min = q;
	}
	printf("max service: %s (%d years)\n", max->name, service(max));
	printf("min service: %s (%d years)\n", min->name, service(min));
}
