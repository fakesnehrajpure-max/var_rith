#include <stdio.h>
#include <stdlib.h>

int *arr;
int n;
int count;

void create_array(int n);
int insert(int i, int data);
int delete(int i);
int max_array();
int min_array();
void display();
void reverse_display();
int search(int element);
float avg_array();
int has(int a[], int n, int elem);
int duplicates();
void reverse();
int main() {
    int choice, i, data, min, max;
    float avg;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    create_array(n);

    printf("1: insert element\n2: delete element\n3: minimum value\n4: maximum value"
          "\n5: display array\n6: reverse display array\n7: search element\n8: count of elements"
          "\n9: average\n10: check for duplicates\n11: reverse array\n\n");
    while(1) {
        printf("enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1: 
            printf("Enter index: "); scanf("%d", &i);
            printf("Enter data: "); scanf("%d", &data);
            if(insert(i, data) == 0) printf("element inserted\n");
            else printf("invalid index\n");
            break; 

            case 2: 
            printf("Enter index: "); scanf("%d", &i);
            if(delete(i) == 0) printf("element deleted\n");
            else printf("invalid index\n");
            break;

            case 3:
            min = min_array();
            if(min != -1) printf("min element of array: %d\n", min); 
            else printf("no elements in array\n");
            break;
            
            case 4:
            max = max_array();
            if(max != -1) printf("max element of array: %d\n", max); 
            else printf("no elements in array\n");
            break;

            case 5:
            display();
            break;

            case 6:
            reverse_display();
            break;

            case 7:
            printf("Enter element: "); scanf("%d", &data);
            i = search(data);
            if(i != -1) printf("%d found at index %d\n", data, i);
            else printf("%d not in array\n", data);
            break;

            case 8:
            printf("number of elements in array: %d\n", count);
            break;
            
            case 9:
            avg = avg_array();   
            if(avg != -1) printf("average of array: %.2f\n", avg);
            else printf("no elements in array\n");
            break;

            case 10:
            data = duplicates();
            if(data != -1) printf("element %d has a duplicate\n", data);
            else printf("there are no duplicates\n");
            break;

            case 11:
            reverse();
            printf("array has been reversed\n");
            break;
            
            default:
            printf("invalid choice\n");
            break;
        }
        fputc('\n', stdout);
    }
    return 0;
}

void create_array(int n) {
    arr = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    count = n;
}

int insert(int i, int data) {
    if(i < 0 || i >= n) {
        return -1;
    } else {
        arr[i] = data;
        if(count != n) count++;
        return 0;
    }
    
}

int delete(int i) {
    if(i < 0 || i >= n) {
        return -1;
    } else {
        arr[i] = -1;
        count--;
        return 0;
    }
}

int max_array() {
    int i = 0, max_l;
    max_l = arr[i];
    while(max_l == -1) {
        if(i >= n) return -1;
        max_l = arr[i];
        i++;
    } 
    while(i < n) {
        if(arr[i] != -1) {
            if(max_l < arr[i]) max_l = arr[i];
        }
        i++;
    }
    return max_l;
}

int min_array() {
    int i = 0, min_l;
    min_l = arr[i];
    while(min_l == -1) {
        if(i >= n) return -1;
        min_l = arr[i];
        i++;
    }
    while(i < n) {
        if(arr[i] != -1) {
            if(min_l > arr[i]) min_l = arr[i];
        }
        i++;
    }
    return min_l;
}

void display() {
    for(int i = 0; i < n; i++) {
        if(arr[i] != -1) printf("%d: %d\n", i, arr[i]);
    }
}

void reverse_display() {
    for(int i = n-1; i >= 0; i--) {
        if(arr[i] != -1) printf("%d: %d\n", i, arr[i]);
    }
}

int search(int element) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == element) return i;
    }

    return -1;
}

int count_array() {
    return count;
}

float avg_array() {
    if(count <= 0) return -1;
    float sum = 0;
    for(int i = 0; i < n; i++) {
        if(arr[i] != -1) sum += arr[i];
    }

    return sum/count;
}

int has(int a[], int n, int elem) {
    for(int i = 0; i < n; i++) {
        if(a[i] == elem) return 1;
    }
    return 0;
}

int duplicates() {
    int unique[count];
    int unique_i = 0;
    for(int i = 0; i < count; i++) unique[i] = -1;
    for(int i = 0; i < n; i++) {
        if(arr[i] != -1) {
            if(has(unique, unique_i, arr[i])) return arr[i];
            else unique[unique_i] = arr[i];
            unique_i++;
        }
    }
    return -1;
}

void reverse() {
    int *first = arr;
    int *last = arr + n - 1;
    int temp;
    for(int i = 1; i <= count/2; i++) {
        while(*first == -1) first++;
        while(*last == -1) last--;
        temp = *first;
        *first = *last;
        *last = temp;

        first++;
        last--;
    }
}