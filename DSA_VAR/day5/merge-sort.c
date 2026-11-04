#include <stdio.h>
void mergesort(int arr[], int left, int right);
void merge(int arr[], int left, int mid, int right);
void display(int arr[], int n);
int main() {
    int n;
    printf("Enter size of arrays: ");
    scanf("%d", &n);
    int arr[2*n];
    printf("Enter elements of first array:\n");
    for(int i = 0; i < n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &(arr[i]));
    }
    printf("Enter elements of second array:\n");
    for(int i = n; i < 2*n; i++) {
        printf("Enter element %d: ", i-n);
        scanf("%d", &(arr[i]));
    }
    mergesort(arr, 0, 2*n-1);
    printf("\nSorted and merged:\n");
    display(arr, 2*n);

}

void mergesort(int arr[], int left, int right) {
    if(!(left < right)) return;
    int mid = (left + right)/2;
    mergesort(arr, left, mid);
    mergesort(arr, mid+1, right);
    merge(arr, left, mid, right);
}

void merge(int arr[], int left, int mid, int right) {
    int n_left = mid - left + 1;
    int n_right = right - mid;
    int a_left[n_left];
    int a_right[n_right];
    for(int i = 0; i < n_left; i++) a_left[i] = arr[left+i];
    for(int i = 0; i < n_right; i++) a_right[i] = arr[mid+i+1];

    int i_left = 0, i_right = 0, i = left;
    while(i_left < n_left && i_right < n_right) {
        if(a_left[i_left] < a_right[i_right]) arr[i++] = a_left[i_left++];
        else arr[i++] = a_right[i_right++];
    }
    while(i_left < n_left) arr[i++] = a_left[i_left++];
    while(i_right < n_right) arr[i++] = a_right[i_right++];
}

void display(int arr[], int n) {
    for(int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}