#include <stdio.h>
#include <stdlib.h>

typedef struct STACKARR
{
    int size;
    int top;
    char *stk_ptr;
} STACK;

STACK *init_Stack(STACK *S);
int isFull(STACK *S);
int isEmpty(STACK *S);
STACK *PUSH(STACK *S, char val);
void DISPLAY(STACK *S);

int main()
{
    STACK S;

    init_Stack(&S);

    for (char c = 'A'; c <= 'Z'; c++)
    {
        PUSH(&S, c);
    }

    DISPLAY(&S);

    free(S.stk_ptr);
    return 0;
}

STACK *init_Stack(STACK *S)
{
    S->size = 26;
    S->top = -1;
    S->stk_ptr = malloc(S->size * sizeof(char));

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

STACK *PUSH(STACK *S, char val)
{
    if (isFull(S))
    {
        printf("Stack Overflow! Cannot push.\n");
        return S;
    }

    S->stk_ptr[++S->top] = val;
    return S;
}

void DISPLAY(STACK *S)
{
    if (isEmpty(S))
    {
        printf("Stack empty!\n");
        return;
    }

    printf("Stack elements in reverse order:\n");
    for (int i = S->top; i >= 0; i--)
    {
        printf("%c ", S->stk_ptr[i]);
    }
    printf("\n");
}