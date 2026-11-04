#include <stdio.h>
int a[10] = {12, 23, 34, 45, 56, 67, 78, 89, 90, 98};
int key;
void linear_search(int arr[], int size, int k);
void binary_search_it(int arr[], int k, int low, int high);
void binary_search_rec(int arr[], int k, int low, int high);
int main() {
    printf("Enter key: ");
    scanf("%d", &key);
//    linear_search(a, 10, key);
    // binary_search(a,key, 0,9);
    binary_search_rec(a, key, 0, 10);
    return 0;
}

void linear_search(int arr[], int size, int k) {
    for(int i = 0; i < size; i++) {
        if(arr[i] == k) {
            printf("%d found at %d\n", key, i);
            return;
        }
    }
    printf("%d not found\n", k);
}

void binary_search_it(int arr[], int k, int low, int high) {
    int i, mid,l,h;
    l =low; h= high;
    while(l<=h)
    {
    mid = (l+h)/2;

       if(arr[mid] == k)
        {
        printf("Key %d found in the array\n", k);
        return;
        }
        if(arr[mid]< key)
        {
        l = mid +1 ;
        }
        else{
        h = mid-1 ;
         }
    }
    printf("%d not found\n", k);   
}
void binary_search_rec(int arr[], int k, int low, int high)
{
    if(low > high) {
        printf("%d not found\n", key);
        return;
    }
    int mid = (low+high)/2;
    if(arr[mid] == key) {
        printf("%d found\n", key);
        return;
    } else if(arr[mid] < key) {
        binary_search_rec(arr, k, mid+1, high);
    } else if(arr[mid] > key) {
        binary_search_rec(arr, k, low, mid-1);
    }
}