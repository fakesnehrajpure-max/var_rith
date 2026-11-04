#include <stdio.h>
#include <stdlib.h>

typedef struct node_internal {
    int data;
    struct node_internal *next;
} node;

node* createNode(int val);
node* addAtStart(int val, node* head);
node* addAtEnd(int val, node* head);
node* deleteAtStart(node* head);
node* deleteAtEnd(node* head);
void display(node* head);
void free_all(node* head);

int main() {
    node *head = NULL;
    int choice, data;
    printf("0: exit\n1: display\n2: add at start\n3: add at end\n"
           "4: delete at start\n5: delete at end\n\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                free_all(head);
                exit(0);
                break;
            case 1:
                display(head); break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                head = addAtStart(data, head);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                head = addAtEnd(data, head);
                break;
            case 4:
                head = deleteAtStart(head);
                break;
            case 5:
                head = deleteAtEnd(head);
                break;
        }
    }
}

node* createNode(int val) {
    node *new = malloc(sizeof(node));
    new->data = val;
    new->next = NULL;
    return new;
}

node* addAtStart(int val, node* head) {
    node *new = createNode(val);
    if(!head) {
        head = new;
        head->next = head;
    } else {
        node *temp = head;
        while(temp->next != head) temp = temp->next;
        new->next = head;
        temp->next = new;
        head = new;
    }
    return head;
}

node* addAtEnd(int val, node* head) {
    node *new = createNode(val);
    if(!head) {
        head = new;
        head->next = head;
    } else {
        node *temp = head;
        while(temp->next != head) temp = temp->next;
        temp->next = new;
        new->next = head;
    }
    return head;
}

node* deleteAtStart(node* head) {
    if(!head) printf("The list is empty\n");
    else if(head->next == head) {
        free(head);
        head = NULL;
    } else {
        node *temp = head;
        while(temp->next != head) temp = temp->next;
        node *del = head;
        head = head->next;
        temp->next = head;
        free(del);
    }
    return head;
}

node* deleteAtEnd(node* head) {
    if(!head) printf("The list is empty\n");
    else if(head->next == head) {
        free(head);
        head = NULL;
    } else {
        node *temp = head;
        while(temp->next->next != head) temp = temp->next;
        node *del = temp->next;
        temp->next = head;
        free(del);
    }
    return head;
}

void display(node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        do {
            printf("%d", temp->data);
            temp = temp->next;
            if(temp != head) printf(" -> ");
        } while(temp != head);
        printf("\n");
    }
}

void free_all(node* head) {
    if(!head) return;
    node *temp = head;
    node *next_node;
    do {
        next_node = temp->next;
        free(temp);
        temp = next_node;
    } while(temp != head);
}