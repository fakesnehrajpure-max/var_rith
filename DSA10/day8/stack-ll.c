#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct node_internal {
    int data;
    struct node_internal *next;
} node;

void display(node *top);
void push(node **top, int val);
int is_empty(node *top);
node* create_node(int val);
int pop(node **top);
int peek(node *top);
int main() {
    int choice, val;
    node *top = NULL;
    printf("0: quit\n1: display\n2: push\n3: pop\n4: peek\n5: is empty\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                exit(0);
                break;
            case 1:
                display(top);
                break;
            case 2:
                printf("Enter value to be pushed: ");
                scanf("%d", &val);
                push(&top, val);
                break;
            case 3:
                val = pop(&top);
                if(val == INT_MAX) printf("Stack is empty\n");
                else printf("Value popped = %d\n", val);
                break;
            case 4:
                val = peek(top);
                if(val == INT_MAX) printf("Stack is empty\n");
                else printf("Value at top = %d\n", val);
                break;
            case 5:
                if(is_empty(top)) printf("Stack is empty\n");
                else printf("Stack is not empty\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
            }
    }
    return 0;
}
int is_empty(node *top) {
    return (top == NULL);
}

void display(node *top) {
    if(is_empty(top)) printf("Stack is empty\n");
    else {
        printf("Stack:\n");
        node *temp = top;
        while(temp) {
            printf("%d\n", temp->data);
            temp = temp->next;
        }
    }
}

node* create_node(int val) {
    node *temp = malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

void push(node **top, int val) {
    if(*top == NULL) {
        *top = create_node(val);
    } else {
        node *temp = *top;
        *top = create_node(val);
        (*top)->next = temp;
    }
}

int pop(node **top) {
    if(*top == NULL) return INT_MAX;
    else {
        int temp_data = (*top)->data;
        node *temp_next = (*top)->next;
        free(*top);
        *top = temp_next;
        return temp_data;
    }
}

int peek(node *top) {
    if(top == NULL) return INT_MAX;
    else return top->data;
}