#include <stdio.h>
#include <stdlib.h>
#define CURRENT_YEAR 2026

typedef struct {
    int id;
    char name[100];
    float sal;
    int year;
} employee;

int n;
employee **emps;
int *yos;

void create_emp_arr(int n);
void get_emp_data(int i);
float total_salary();
float avg_salary();
float max_salary();
float min_salary();
void years_of_service();
int max_service();
int min_service();
int main() {
    printf("enter number of employees: ");
    scanf("%d", &n);
    create_emp_arr(n);
    for(int i = 0; i < n; i++) {
        printf("enter detail of employee %d:\n", i);
        get_emp_data(i);
    }
    fputc('\n', stdout);
    fputc('\n', stdout);
    printf("total salary: %.2f\n", total_salary());
    printf("avg salary: %.2f\n", avg_salary());
    printf("max salary: %.2f\n", max_salary());
    printf("min salary: %.2f\n", min_salary());

    years_of_service();
    fputc('\n', stdout);
    printf("years of service of each employee:\n");
    for(int i = 0; i < n; i++) {
        printf("%s: %d years\n", emps[i]->name, yos[i]);
    }
    fputc('\n', stdout);
    printf("employee with max service:\n");
    printf("%s: %d years\n", emps[max_service()]->name, yos[max_service()]);
    fputc('\n', stdout);
    printf("employee with min service:\n");
    printf("%s: %d years\n", emps[min_service()]->name, yos[min_service()]);

    return 0;
}

void create_emp_arr(int n) {
    emps = (employee**) malloc(n * sizeof(employee*));
    yos = (int*) malloc(n * sizeof(int));
}

void get_emp_data(int i) {
    static int id = 0;
    float sal; int year;
    emps[i] = (employee*) malloc(sizeof(employee));;
    emps[i]->id = id;
    
    printf("enter employee %d name: ", id);
    fgetc(stdin);
    fgets(emps[i]->name, sizeof(emps[i]->name), stdin);
    char* c = emps[i]->name;
    while(*c != '\n') c++;
    *c = '\0';
    
    printf("enter employee %d salary: ", id);
    scanf("%f", &sal);
    emps[i]->sal = sal;
    
    printf("enter employee %d year of joining: ", id);
    scanf("%d", &year);
    emps[i]->year = year;
    
    id++;
}

float total_salary() {
    float total = 0;
    for(int i = 0; i < n; i++) total += emps[i]->sal;
    return total;
}
float avg_salary() {
    return total_salary()/n;
}
float max_salary() {
    float max = emps[0]->sal;
    for(int i = 0; i < n; i++) {
        if(max < emps[i]->sal) max = emps[i]->sal;
    };
    return max;    
}
float min_salary() {
    float min = emps[0]->sal;
    for(int i = 0; i < n; i++) {
        if(min > emps[i]->sal) min = emps[i]->sal;
    };
    return min;
}

void years_of_service() {
    for(int i = 0; i < n; i++) yos[i] = CURRENT_YEAR - emps[i]->year + 1;
}

int max_service() {
    int max = 0;
    for(int i = 0; i < n; i++) {
        if(yos[max] < yos[i]) max = i;
    }
    return max;
}
int min_service() {
    int min = 0;
    for(int i = 0; i < n; i++) {
        if(yos[min] > yos[i]) min = i;
    }
    return min;
}