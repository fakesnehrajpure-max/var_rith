#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node_internal {
    int data;
    struct node_internal *next;
} node;

void display(node *front);
void enqueue(node **front, node **rear, int val);
node* create_node(int val);
int dequeue(node **front, node **rear);
int main() {
    int choice, val;
    node *front = NULL;
    node *rear = NULL;
    printf("0: quit\n1: display\n2: enqueue\n3: dequeue\n4: front\n5: rear\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                exit(0);
                break;
            case 1:
                display(front);
                break;
            case 2:
                printf("Enter value to be enqueued: ");
                scanf("%d", &val);
                enqueue(&front, &rear, val);
                break;
            case 3:
                val = dequeue(&front, &rear);
                if(val == INT_MAX) printf("Queue is empty\n");
                else printf("Dequeued value = %d\n", val);
                break;
            case 4:
                if(front) printf("Value at front = %d\n", front->data);
                else printf("Queue is empty\n");
                break;
            case 5:
                if(rear) printf("Value at rear = %d\n", rear->data);
                else printf("Queue is empty\n");
                break;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
    return 0;
}

void display(node *front) {
    if(front == NULL) printf("Queue is empty\n");
    else {
        printf("(IN) ");
        node *temp = front;
        while(temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("(OUT)\n");
    } 
}

void enqueue(node **front, node **rear, int val) {
    if(*front ==  NULL) {
        *front = create_node(val);
        *rear = *front;
    } else {
        node *temp = *front;
        *front = create_node(val);
        (*front)->next = temp;
    }
}
node* create_node(int val) {
    node *temp = malloc(sizeof(node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

int dequeue(node **front, node **rear) {
    if(*front == NULL) return INT_MAX;
    else if(*front == *rear) {
        int temp_data = (*front)->data;
        free(*front);
        *front = NULL;
        *rear = NULL;
        return temp_data;
    } else {
        node *temp = *front;
        while(temp->next != *rear) temp = temp->next;
        int temp_data = (*rear)->data;
        free(*rear);
        *rear = temp;
        (*rear)->next = NULL;
        return temp_data;
    }
}