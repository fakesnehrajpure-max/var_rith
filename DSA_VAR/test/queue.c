#include <stdio.h>
#include <limits.h>
#define MAXQSIZE 5
int queue[MAXQSIZE];
int front = -1, rear = -1;

int is_full() {
    return ((rear+1) % MAXQSIZE == front);
}

int is_empty() {
    return (front == -1);
}


void display() {
    int length;
    if(is_empty()) printf("Queue is empty\n");
    else {
        if(rear >= front) length = rear - front + 1;
        else length = rear + 1 + MAXQSIZE - front;
        for(int i = 0; i < length; i++) printf("%d ", queue[(front+i)%MAXQSIZE]);
        printf("rear = %d, front = %d\n", rear, front);
    }
}

void insert(int data) {
    if(is_full()) {
        printf("Queue is full\n");
        return;
    }
    rear++;
    rear %= MAXQSIZE;
    queue[rear] = data;
    if(front == -1) front++;
}

int delete() {
    int data;
    if(is_empty()) {
        printf("Queue is empty\n");
        return INT_MAX;
    }
    data = queue[front];
    if(front == rear) {front = rear = -1;}
    else {
        front++;
        front %= MAXQSIZE;
    }
    return data;
}

int main() {
    insert(5);
    display();
    insert(10);
    display();
    insert(15);
    display();
    insert(20);
    display();
    insert(25);
    display();
    insert(30);
    display();
    delete();
    display();
    delete();
    display();
    delete();
    display();
    delete();
    display();
    insert(30);
    display();
    delete();
    display();
    delete();
    display();
    return 0;
}