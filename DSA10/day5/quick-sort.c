#include <stdio.h>
void display(int arr[], int n);
void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
int main() {
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &(arr[i]));
    }
    quicksort(arr, 0, n-1);
    printf("Quicksort:\n");
    display(arr, n);
    return 0;
}

void quicksort(int arr[], int low, int high) {
    if(!(low < high)) return;
    int pivot = partition(arr, low, high);
    quicksort(arr, low, pivot-1);
    quicksort(arr, pivot+1, high);
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int low_index = low-1;
    int temp;
    for(int i = low; i < high; i++)  {
        if(arr[i] < pivot) {
            temp = arr[i];
            arr[i] = arr[++low_index];
            arr[low_index] = temp;
        }
    }
    temp = arr[++low_index];
    arr[low_index] = arr[high];
    arr[high] = temp;
    return low_index;
}

void display(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}
