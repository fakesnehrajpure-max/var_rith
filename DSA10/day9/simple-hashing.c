#include <stdio.h>

int hashCode(int val) {
    return val % 10;
}

void insert(int arr[], int val) {
    int insert_index = hashCode(val);
    while(1) {
        if(arr[insert_index] == -1) {
            arr[insert_index] = val;
            return;
        }
        insert_index = (insert_index + 1) % 10;
    }
}

void search(int arr[], int val) {
    int search_index = hashCode(val);
    for(int i = 0; i < 10; i++) {
        if(arr[search_index] == val) {
            printf("%d found\n", val);
            return;
        }
        search_index = (search_index + 1) % 10;
    }
    printf("%d not found\n", val);
}

int main() {
    int arr[10], val;
    for(int i = 0; i < 10; i++) arr[i] = -1;
    printf("Enter values to be inserted:\n");
    for(int i = 0; i < 10; i++) {
        printf("Enter value %d: ", i);
        scanf("%d", &val);
        insert(arr, val);
    }

    printf("Hash Table:\n");
    for(int i = 0; i < 10; i++) printf("%d: %d\n", i, arr[i]);
    while(1) {
        printf("Enter value to be searched: ");
        scanf("%d", &val);
        search(arr, val);
    }
}