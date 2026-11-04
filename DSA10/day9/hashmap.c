#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

typedef struct n {
    int data;
    struct n *next;
} node;

typedef struct {
    int key;
    node *head;
} bucket;

int hashCode(int key) {
    return key%SIZE;
}

void insert(node *hashmap[], int val) {
    int hash = hashCode(val);
    if(hashmap[hash] == NULL) {
        hashmap[hash] = malloc(sizeof(node));
        hashmap[hash]->data = val;
        hashmap[hash]->next = NULL;
    } else {
        node *temp = hashmap[hash];
        hashmap[hash] = malloc(sizeof(node));
        hashmap[hash]->data = val;
        hashmap[hash]->next = temp;
    }
}

void display(node *hashmap[]) {
    for(int i = 0; i < SIZE; i++) {
        if(hashmap[i] == NULL) printf("%d: Empty\n", i);
        else {
            printf("%d: ", i);
            node *temp = hashmap[i];
            while(temp) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }
            putchar('\n');
        }
    }
}

int main() {
    node *hashmap[SIZE];
    for(int i = 0; i < SIZE; i++) hashmap[i] = NULL;
    int choice, val;
    printf("0: exit\n1: display\n2: insert\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                exit(0);
            case 1:
                display(hashmap);
                break;
            case 2:
                printf("Enter value to be inserted: ");
                scanf("%d", &val);
                insert(hashmap, val);
                break;
        }
    }
}