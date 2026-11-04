#include <stdio.h>
#include <stdlib.h>

typedef int integer;

typedef struct STACKARR
{
    int size;
    int top;
    int *stk_ptr;
} STACK;

STACK *init_Stack(STACK *S);
int isFull(STACK *S);
int isEmpty(STACK *S);
STACK *PUSH(STACK *S);
STACK *POP(STACK *S);
void PEEK(STACK *S);
void DISPLAY(STACK *S);

int main()
{
    STACK S;
    int choice;

    init_Stack(&S);

    do
    {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Peek\n");
        printf("4. Display\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            PUSH(&S);
            break;
        case 2:
            POP(&S);
            break;
        case 3:
            PEEK(&S);
            break;
        case 4:
            DISPLAY(&S);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 5);

    free(S.stk_ptr);
    return 0;
}

STACK *init_Stack(STACK *S)
{
    printf("Enter the size of the stack: ");
    scanf("%d", &S->size);

    S->top = -1;
    S->stk_ptr = malloc(S->size * sizeof(int));

    if (S->stk_ptr == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    return S;
}

int isFull(STACK *S)
{
    return S->top == S->size - 1;
}

int isEmpty(STACK *S)
{
    return S->top == -1;
}

STACK *PUSH(STACK *S)
{
    int val;

    if (isFull(S))
    {
        printf("Stack Overflow! Cannot push.\n");
        return S;
    }

    printf("Enter value: ");
    scanf("%d", &val);

    S->stk_ptr[++S->top] = val;
    printf("%d pushed to stack.\n", val);
    return S;
}

STACK *POP(STACK *S)
{
    if (isEmpty(S))
    {
        printf("Stack Underflow so Cannot pop.\n");
        return S;
    }

    printf("%d popped from stack.\n", S->stk_ptr[S->top--]);
    return S;
}

void PEEK(STACK *S)
{
    if (isEmpty(S))
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Top element: %d\n", S->stk_ptr[S->top]);
}

void DISPLAY(STACK *S)
{
    if (isEmpty(S))
    {
        printf("Stack empty!\n");
        return;
    }

    printf("Stack elements :\n");
    for (int i = S->top; i >= 0; i--)
    {
        printf(" %d \n", S->stk_ptr[i]);
    }
}