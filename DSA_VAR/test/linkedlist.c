#include <stdio.h>
#include <stdlib.h>

typedef struct node_internal {
    int data;
    struct node_internal *next;
} node;

node *head = NULL;

void insert_begin(int val);
void insert_end(int val);
void display();
int main() {
        int n;
    printf("Enter number of elements in list: ");
    scanf("%d", &n);
    for(int i = n; i >= 1; i--) insert_begin(i);
    display();
    return 0;
    return 0;
}

void insert_begin(int val) {
    node *new = malloc(sizeof(node));
    new->data = val;
    new->next = NULL;
    if(head) new->next = head;
    head = new;
}

void insert_end(int val) {
    node *temp = head;
    node *new = malloc(sizeof(node));
    new->data = val;
    new->next = NULL;
    if(!head) head = new;
    else {
        while(temp->next != NULL) temp = temp->next;
        temp->next = new; 
    }    
}

void display() {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        while(temp) {
            printf("%d", temp->data);
            if(temp = temp->next) printf(" -> ");
        }
        printf("\n");
    }
}