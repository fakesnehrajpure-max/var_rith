#include <stdio.h>
void display(int arr[], int n);
void quicksort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
void mergesort(int arr[], int low, int high);
void merge(int arr[], int low, int mid, int high);
void main() {
    int arr[] = {12, 5, 17, 20, 9, 11, 25, 2, 7, 15};
    int size = (sizeof(arr)/sizeof(arr[0]));
    // quicksort(arr, 0, size - 1);
    mergesort(arr, 0, size - 1);
    display(arr, size);
}
void quicksort(int arr[], int low, int high) {
    int pi;
    if(low < high) {
        pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    int temp;
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            printf("swapping i = %d j = %d\n", i, j);
            display(arr, 10);
        } else {
            printf("no swap i = %d j = %d\n", i, j);
            display(arr, 10);
        }
    }
    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void mergesort(int arr[], int left, int right) {
    int mid; 
    if(left < right) {
        mid = (right + left)/2;
        mergesort(arr, left, mid);
        mergesort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}
void merge(int arr[], int left, int mid, int right) {
    int n_left = mid - left + 1;
    int n_right = right - mid;
    int i = 0, j = 0, k = 0;
    int l_array[n_left];
    int r_array[n_right];
    for(i = 0; i < n_left; i++) l_array[i] = arr[left+i];
    for(i = 0; i < n_right; i++) r_array[i] = arr[mid+1+i];
    for(i=0,j=0,k=left; (i < n_left && j < n_right); k++) {
        if(l_array[i] < r_array[j]) arr[k] = l_array[i++];
        else arr[k] = r_array[j++];
    }
    while(i < n_left) arr[k++] = l_array[i++];
    while(j < n_right) arr[k++] = r_array[j++];
}

void display(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}