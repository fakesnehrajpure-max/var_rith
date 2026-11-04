#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef struct {
    int *arr;
    int front;
    int rear;
    int size;
} queue;

queue* init_queue();
int is_full(queue *q);
int is_empty(queue *q);
void enqueue(queue *q, int val);
int dequeue(queue *q);
void display(queue *q);
int main() {
    int choice, val;
    queue *q;
    printf("1: init queue\n2: enqueue\n3: dequeue\n4: display\n\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                q = init_queue();
                break;
            case 2:
                printf("Enter value to be enqueued: ");
                scanf("%d", &val);
                enqueue(q, val);
                break;
            case 3:
                val = dequeue(q);
                if(val != INT_MAX) printf("Dequeued value = %d\n", val);
                break;
            case 4:
                display(q);
                break; 
        }
    }
}

queue* init_queue() {
    int size;
    printf("Enter the size of queue: ");
    scanf("%d", &size);
    queue *q = (queue*)malloc(sizeof(queue));
    q->arr = (int *)malloc(size*sizeof(int));
    q->rear = -1;
    q->front = -1;
    q->size = size; 
    return q;
}

int is_empty(queue *q) {
    return (q->front == -1 || (q->front > q->rear));
}

int is_full(queue *q) {
    return (q->rear + 1 >= q->size);
}

void enqueue(queue *q, int val) {
    if(is_full(q)) {
        printf("Queue is full\n");
        return;
    }
    q->rear++;
    q->arr[q->rear] = val;
    if(q->front == -1) q->front = 0;
}

int dequeue(queue *q) {
    if(is_empty(q)) {
        printf("Queue is empty\n");
        return INT_MAX;
    }
    int data = q->arr[q->front];
    if(q->front == q->size - 1) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    
    return data;
}

void display(queue *q) {
    if(is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    for(int i = q->front; i <= q->rear; i++) printf("%d ", q->arr[i]);
}