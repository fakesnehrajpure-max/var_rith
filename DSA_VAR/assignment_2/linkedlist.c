#include <stdio.h>
#include <stdlib.h>

typedef struct node_internal {
    int data;
    struct node_internal *next;
} node;

node* insert_begin(int val, node* head);
node* insert_end(int val, node* head);
node* remove_begin(node* head);
node* remove_end(node* head);
void display(node* head);
int count(node* head);
void search(int val, node* head);
node* insert_pos(int val, int pos, node* head);
node* delete_pos(int pos, node* head);
node* insert_data(int val, int find, node* head);
node* delete_data(int find, node* head);
void free_all(node* head);
void reverse_display(node *head, node* start);
int main() {
    node *head = NULL;
    int choice, data, pos, find;
    printf("0: exit\n1: display\n2: insert in beginning\n3: insert at end\n"
           "4: remove from beginning\n5: remove from end\n6: number of nodes\n"
           "7: search node\n8: insert at position\n9: delete at position\n"
           "10: insert node after node with given data\n11: delete node containing given data\n"
           "12: display in reverse\n\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
                free_all(head);
                exit(0);
                break;
            case 1:
                display(head); break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insert_begin(data, head);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                head = insert_end(data, head);
                break;
            case 4:
                head = remove_begin(head);
                break;
            case 5:
                head = remove_end(head);
                break;
            case 6:
                printf("There are %d nodes in the list\n", count(head));
                break;
            case 7:
                printf("Enter data: ");
                scanf("%d", &data);
                search(data, head);
                break;
            case 8:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &pos);
                head = insert_pos(data, pos, head);
                break;  
            case 9:
                printf("Enter position: ");
                scanf("%d", &pos);
                head = delete_pos(pos, head);
                break;
            case 10:
                printf("Enter data after which to be inserted: ");
                scanf("%d", &find);
                printf("Enter data to be inserted: ");
                scanf("%d", &data);
                head = insert_data(data, find, head);
                break;
            case 11:
                printf("Enter data to be deleted: ");
                scanf("%d", &find);
                head = delete_data(find, head);
                break;
            case 12:
                reverse_display(head, head);
                break;
        }
    }
}

node* insert_begin(int val, node* head) {
    node *new = malloc(sizeof(node));
    new->data = val;
    new->next = NULL;
    if(!head) head = new;
    else {
        new->next = head;
        head = new;
    }
    return head;
}

node* insert_end(int val, node* head) {
    node *temp = head;
    node *new = malloc(sizeof(node));
    new->data = val;
    new->next = NULL;
    if(!head) head = new;
    else {
        while(temp->next != NULL) temp = temp->next;
        temp->next = new; 
    }    
    return head;
}

node* remove_begin(node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node* temp = head;
        head = head->next;
        free(temp);
    }
    return head;
}

node* remove_end(node* head) {
    if(!head) printf("The list is empty\n");
    else if(head->next == NULL) {
        free(head);
        head = NULL;
    }
    else {
        node* temp = head;
        while(!(temp->next != NULL && temp->next->next == NULL)) temp = temp->next;
        free(temp->next);
        temp->next = NULL;
    }
    return head;
}

int count(node* head) {
    int c = 0;
    node *temp = head;
    while(temp) {
        c++;
        temp = temp->next;
    }
    return c;
}

void search(int val, node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        while(temp) {
            if(temp->data == val) {
                printf("%d found in the list\n", val);
                return;
            }
            temp = temp->next;
        }
        printf("%d not found in the list\n", val);
    }
}

node* insert_pos(int val, int pos, node* head) {
    if(pos <= 0 || pos > count(head) + 1) {
        printf("Invalid position\n");
        return head;
    }
    if(pos == 1) {
        insert_begin(val, head);
    } else {
        node *new = malloc(sizeof(node));
        new->data = val;
        new->next = NULL;
        
        int i = 2;
        node *temp = head;
        while(i < pos) {
            temp = temp->next;
            i++;
        }

        new->next = temp->next;
        temp->next = new;
    }
    return head;
}

node* delete_pos(int pos, node* head){
    if(pos <= 0 || pos > count(head)) {
        printf("Invalid position\n");
        return head;
    }
    if(pos == 1) {
        remove_begin(head);
    } else {
        int i = 1;
        node *temp = head;
        while(i < pos - 1) {
            temp = temp->next;
            i++;
        }
        node *rem = temp->next;
        temp->next = temp->next->next;
        free(rem);
    }
    return head;
}

node* insert_data(int val, int find, node* head) {
    node *temp = head;
    while(temp) {
        if(temp->data == find) {
            node *new = malloc(sizeof(node));
            new->data = val;
            new->next = temp->next;
            temp->next = new;
            return head;
        }
        temp = temp->next;
    }
    printf("%d not found in list\n", find);
    return head;
}

node* delete_data(int find, node* head) {
    node *temp = head;
    if(temp && temp->data == find) {
        head = temp->next;
        free(temp);
        return head;
    }
    while(temp) {
        if(temp->next && temp->next->data == find) {
            node *rem = temp->next;
            temp->next = temp->next->next;
            free(rem);
            return head;
        }
        temp = temp->next;
    }
    printf("%d not found in list\n", find);
    return head;
}

void display(node* head) {
    if(!head) printf("The list is empty\n");
    else {
        node *temp = head;
        while(temp) {
            printf("%d", temp->data);
            if(temp = temp->next) printf(" -> ");
        }
        printf("\n");
    }
}

void reverse_display(node *head, node *start) {
    if(head == NULL) {
        printf("The list is empty\n");
        return;
    }
    if(!start) return;
    reverse_display(head, start->next);
    printf("%d", start->data);
    if(start != head) printf(" <- ");
    else printf("\n");
}

void free_all(node* head){
    if(head == NULL) return;
    free_all(head->next);
    free(head);
}