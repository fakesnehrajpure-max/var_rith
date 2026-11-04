#include<stdio.h>
#include<stdlib.h>

void input_n_print(int *arr,int count);
void insertion_sort(int *arr,int n);
void selection_sort(int *arr,int n);
void bubble_sort(int *arr,int n);

int main()
{   
    int count, choice;
    printf("\nEnter the number of elements: ");
    scanf("%d",&count);
    int *arr =NULL;
    arr = malloc(count * sizeof(int));

    input_n_print(arr,count);
    
    printf("\n\n====SORTING MENU====");
    printf("\n1. Selection Sort");
    printf("\n2. Insertion Sort");
    printf("\n3. Bubble Sort");
    printf("\nEnter your choice (1-3): ");
    scanf("%d", &choice);
    
    printf("\nSorted array: ");
    
    switch(choice)
    {
        case 1:
            selection_sort(arr, count);
            break;
        case 2:
            insertion_sort(arr, count);
            break;
        case 3:
            bubble_sort(arr, count);
            break;
        case 4:

            break;
        default:
            printf("\nInvalid choice!");
    }
    
    printf("\n");
    
    free(arr);
    arr= NULL;
    return 0;
     
}

void input_n_print(int *arr,int count)
{
    for(int i = 0; i<count;i++)
    {
        printf("\nEnter the number %d : ",i);
        scanf("%d",&arr[i]);
    }
    printf("\nOriginal array:");
    for(int i =0;i<count;i++)
    {
        printf("%d ",arr[i]);
    }
    
}

void selection_sort(int *arr,int n)
{
    int i, small, temp;

     for ( i = 0; i < n-1; i++)
     {
        small =i;
        
        for(int j = i+1;j<n;j++)
        {
            if (arr[j]< arr[small])
            {
                small = j;
            }
        }

        temp = arr[i];
        arr[i] = arr[small];
        arr[small]= temp;
     }

    for (int i = 0; i < n; i++)
     {
        printf("%d ",arr[i]);
     }
}

void insertion_sort(int *arr,int n)
{
    int i, key, j;

    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

 
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }

    
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}


void bubble_sort(int *arr,int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
            
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    // Print sorted array
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}