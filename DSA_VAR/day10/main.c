#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct e {
    int id;
    char name[30];
    float salary;
    struct e *next;
} emp;

emp *create(int id, char name[], int salary) {
    emp *temp = malloc(sizeof(emp));
    temp->id = id;
    strcpy(temp->name, name);
    temp->salary = salary;
    temp->next = NULL;
    return temp;
}

emp* add(emp *head, int id, char name[], float salary) {
    if(head == NULL) return create(id, name, salary);
    else if(id < head->id)  {
        emp *temp = head;
        head = create(id, name, salary);
        head->next = temp;
        return head;
    } else {
        emp *temp = head;
        while(temp->next) {
            if(temp->next->id > id) {
                emp *temp2 = temp->next;
                temp->next = create(id, name, salary);
                temp->next->next = temp2;
                return head;
            }
            temp = temp->next;
        }
        temp->next = create(id, name, salary);
        return head;
    }
}

void display(emp *head) {
    emp *temp = head;
    while(temp) {
        printf("%d. %s : %f\n", temp->id, temp->name, temp->salary);
        temp = temp->next;
    }
}

int main() {
    int choice;
    int id;
    char name[30];
    float salary;
    emp *head = NULL;
    printf("0: exit\n1: add employee\n2: display\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0: exit(0);
            case 1: 
                printf("Enter employee id: ");
                scanf("%d", &id);
                printf("Enter employee name: ");
                scanf("%s", name);
                printf("Enter employee salary: ");
                scanf("%f", &salary);
                head = add(head, id, name, salary);
                break;
            case 2:
                display(head);
                break;
        }
    }

    return 0;
}