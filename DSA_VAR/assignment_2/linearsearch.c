#include <stdio.h>
#include <stdlib.h>

void iter_search(int arr[], int n, int key);
void recur_search(int arr[], int n, int key);
void iter_display(int arr[], int n);
void recur_display(int arr[], int n);
void iter_reverse_display(int arr[], int n);
void recur_reverse_display(int arr[], int n);

int main() {
    int *arr;
    int n;
    printf("Enter length of array: ");
    scanf("%d", &n);
    arr = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &(arr[i]));
    }
    int key, choice;
    printf("\n1: linear search (iterative and recursive)\n"
           "2: display array (iterative and recursive)\n"
           "3: reverse display array (iterative and recursive)\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("Enter element to be searched: ");
                scanf("%d", &key);
                printf("\nIterative search:\n");
                iter_search(arr, n, key);
                printf("\nRecursive search:\n");
                recur_search(arr, n, key);
                break;
            case 2:
                printf("\nIterative display:\n");
                iter_display(arr, n);
                printf("\nRecursive display:\n");
                recur_display(arr, n);
                break;
            case 3:
                printf("\nIterative reverse display:\n");
                iter_reverse_display(arr, n);
                printf("\nRecursive reverse display:\n");
                recur_reverse_display(arr, n);
                break;
        }
    }

    return 0;
}

void iter_search(int arr[], int n, int key) {
    int found = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == key) {
            printf("%d found at index %d\n", key, i);
            found = 1;
        }
    }
    if(!found) printf("%d not found in array\n", key);
}
void recur_search(int arr[], int n, int key) {
    static int i = 0;
    static int found = 0;
    if(arr[i] == key) {
        printf("%d found at index %d\n", key, i);
        found = 1;
    }
    if(i == n) {
        if(!found) printf("%d not found in array\n", key);
        i = 0;
        return;
    }
    i++;
    recur_search(arr, n, key);
}

void iter_display(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void recur_display(int arr[], int n) {
    static int i = 0;
    if(i == n) {
        printf("\n");
        i = 0;
        return;
    }
    printf("%d ", arr[i]);
    i++;
    recur_display(arr, n);
}

void iter_reverse_display(int arr[], int n) {
    for(int i = n-1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void recur_reverse_display(int arr[], int n) {
    if(n <= 0) {
        printf("\n");
        return;
    }
    printf("%d ", arr[n-1]);
    recur_reverse_display(arr, n-1);

}
