#include <stdio.h>
#include <stdlib.h>

int **rows;
int n_col;
int n_row = 0;

void insert_row();
void delete_row(int index);
void display_rows();
void change_n_col(int n);
int main() {
    int choice, index, data;
    printf("enter number of columns: ");
    scanf("%d", &n_col);
    printf("1: add row\n2: delete row\n3: display rows\n4: change number of columns\n");
    while(1) {
        printf("enter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                insert_row();
                break;
            case 2:
                printf("enter index: ");
                scanf("%d", &index);
                delete_row(index);
                break;
            case 3:
                display_rows();
                break;
            case 4:
                printf("Enter new number of columns: ");
                scanf("%d", &data);
                change_n_col(data);
        }
    }
    return 0;
}

void insert_row() {
    int temp;

    if(n_row == 0) rows = malloc(sizeof(int*));
    else rows = realloc(rows, (n_row+1)*sizeof(int *));

    int *row = (int *) malloc(n_col*sizeof(int));
    rows[n_row] = row;
    
    for(int i = 0; i < n_col; i++) {
        printf("enter element %d of row: ", i);
        scanf("%d", &(rows[n_row][i]));
    }
    n_row++;
}

void delete_row(int index) {
    if(index < 0 || index >= n_row) {
        printf("invalid index\n");
        return;
    }
    free(rows[index]);
    rows[index] = NULL;
}

void display_rows() {
    for(int i = 0; i < n_row; i++) {
        if(rows[i]) {
            printf("%d: ", i);
            for(int j = 0; j < n_col; j++) {
                if(rows[i][j] == -1) printf("<empty> ");
                else printf("%d ", rows[i][j]);
            }
            printf("\n");
        }
    }
}
void change_n_col(int n) {
    n;
    for(int i = 0; i < n_row; i++) {
        if(rows[i]) {
            rows[i] = realloc(rows[i], n*sizeof(int));
            for(int j = n_col; j < n; j++) rows[i][j] = -1;
        }
    }
    n_col = n;
}