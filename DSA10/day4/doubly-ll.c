#include <stdio.h> 

















-
#include <stdlib.h>

typedef struct node_internal {
    int data;
    struct node_internal *prev;
    struct node_internal *next;
} node;

node* createNode(int val);
node* addAtStart(int val, node* head);
node* addAtEnd(int val, node* head);
node* addAtMiddle(int val, int find, node* head);
node* deleteAtStart(node* head);
node* deleteAtEnd(node* head);
node* deleteAtMiddle(int find, node* head);
void display(node* head);
void free_all(node* head);

int main() {
    node *head = NULL;
    int choice, data, find;
    printf("0: exit\n1: display\n2: add at start\n3: add at end\n"
           "4: add at middle\n5: delete at start\n6: delete at end\n"
           "7: delete at middle\n\n");
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
                printf("Enter data after which to be inserted: ");
                scanf("%d", &find);
                printf("Enter data to be inserted: ");
                scanf("%d", &data);
                head = addAtMiddle(data, find, head);
                break;
            case 5:
                head = deleteAtStart(head);
                break;
            case 6:
                head = deleteAtEnd(head);
                break;
            case 7:
                printf("Enter data to be deleted: ");
                scanf("%d", &find);
                head = deleteAtMiddle(find, head);
                break;
        }
    }
}

node* createNode(int val) {
    node *new = malloc(sizeof(node));
    new->data = val;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

node* addAtStart(int val, node* head) {
    node *new = createNode(val);
    if(!head) head = new;
    else {
        new->next = head;
        head->prev = new;
        head = new;
    }
    return head;
}

node* addAtEnd(int val, node* head) {
    node *new = createNode(val);
    if(!head) head = new;
    else {
        node *temp = head;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new;
        new->prev = temp;
    }
    return head;
}

node* addAtMiddle(int val, int find, node* head) {
    node *temp = head;
    while(temp) {
        if(temp->data == find) {
            node *new = createNode(val);
            new->next = temp->next;
            new->prev = temp;
            if(temp->next != NULL) temp->next->prev = new;
            temp->next = new;
            return head;
        }
        temp = temp->next;
    }
    printf("%d not found in list\n", find);
    return head;
}

node* deleteAtStart(node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        head = head->next;
        if(head != NULL) head->prev = NULL;
        free(temp);
    }
    return head;
}

node* deleteAtEnd(node* head) {
    if(!head) printf("The list is empty\n");
    else if(head->next == NULL) {
        free(head);
        head = NULL;
    }
    else {
        node *temp = head;
        while(temp->next != NULL) temp = temp->next;
        temp->prev->next = NULL;
        free(temp);
    }
    return head;
}

node* deleteAtMiddle(int find, node* head) {
    node *temp = head;
    while(temp) {
        if(temp->data == find) {
            if(temp == head) {
                head = head->next;
                if(head != NULL) head->prev = NULL;
            } else {
                temp->prev->next = temp->next;
                if(temp->next != NULL) temp->next->prev = temp->prev;
            }
            free(temp);
            return head;
        }
        temp = temp->next;
    }
    printf("%d not found in list\n", find);
    return head;
}

void display(node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        while(temp) {
            printf("%d", temp->data);
            if(temp->next != NULL) printf(" <-> ");
            temp = temp->next;
        }
        printf("\n");
    }
}

void free_all(node* head) {
    if(head == NULL) return;
    free_all(head->next);
    free(head);
}
