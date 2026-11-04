#include <stdio.h>
#include <stdlib.h>
int array_has(int arr[], int key, int n);
void display(int arr[], int n);
void insert_sorted(int arr[], int n, int val);
void binary_search_it(int arr[], int key, int low, int high);
void binary_search_rec(int arr[], int key, int low, int high);
int main() {
    int *arr = NULL;
    int size;
    int n = 0, temp, key;
    printf("Enter size of array: ");
    scanf("%d", &size);
    arr = malloc(n*sizeof(int));
    while(n < size) {
        printf("Enter element %d: ", n);
        scanf("%d", &temp);
        if(array_has(arr, temp, n)) {
            printf("%d already in array, try again\n", temp);
            continue;
        } else {
            n++;
            if(n == 1) arr = malloc(sizeof(int));
            else arr = realloc(arr, n*sizeof(int));
            insert_sorted(arr, n, temp);
        }
    }
    printf("Sorted array:\n");
    display(arr, n);

    while(1) {
        printf("\nEnter value to be searched: ");
        scanf("%d", &key);
        printf("\nIterative binary search:\n");
        binary_search_it(arr, key , 0, n);
        printf("\nRecursive binary search:\n");
        binary_search_rec(arr, key , 0, n);
    }

    return 0;
}

void insert_sorted(int arr[], int n, int val) {
    if(n == 1) {
        arr[0] = val;
        return;
    }
    int j;
    for(int i = n-1; i >= 0; i--) {
        if(i == 0) arr[i] = val;
        if(arr[i-1] > val) arr[i] = arr[i-1];
        else {
            arr[i] = val;
            return;
        }
    }
}

int array_has(int arr[], int key, int n) {
    if(!arr) return 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] == key) return 1;
    }
    return 0;
}

void display(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void binary_search_it(int arr[], int key, int low, int high) {
    int i, mid, l, h;
    l = low; h = high;
    while(l <= h) {
        mid = (l+h)/2;
        if(arr[mid] == key) {
            printf("%d found in the array\n", key);
            return;
        }
        if(arr[mid] < key) l = mid + 1;
        else if(arr[mid] > key) h = mid - 1;  
    }
    printf("%d not found in the array\n", key);   
}
void binary_search_rec(int arr[], int key, int low, int high) {
    if(low > high) {
        printf("%d not found in the array\n", key);
        return;
    }
    int mid = (low+high)/2;
    if(arr[mid] == key) {
        printf("%d found in the array\n", key);
        return;
    } else if(arr[mid] < key) {
        binary_search_rec(arr, key, mid+1, high);
    } else if(arr[mid] > key) {
        binary_search_rec(arr, key, low, mid-1);
    }
}