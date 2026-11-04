#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b);
void heapify(int arr[], int n, int i);
void heap_sort(int arr[], int n);
void display(int arr[], int n);

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int *arr = malloc(n * sizeof(int));
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &arr[i]);
    }
    heap_sort(arr, n);
    printf("Sorted array: ");
    display(arr, n);
    return 0;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest]) largest = left;
    if(right < n && arr[right] > arr[largest]) largest = right;
    if(largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}   
    
void heap_sort(int arr[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for(int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}   

void display(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}