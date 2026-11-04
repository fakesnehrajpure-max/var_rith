#include <stdio.h>
#include <stdlib.h>

typedef struct node_internal {
    int data;
    struct node_internal *left;
    struct node_internal *right;
    int height;
} node;

int height(node *n);
int max(int a, int b);
node* insert(node *root, int val);
void display(node *root);
node* rotate_left(node *x);
node* rotate_right(node *x);
node* create_node(int val);
node* min_succesor(node *root);
node* delete(node *root, int val);
int search(node *root, int val);
int main() {
    int choice, val;
    node *root = NULL;
    printf("0: exit\n1: display\n2: insert\n3: delete\n4: search\n");
    while(1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 0: exit(0);
            case 1: display(root); break;
            case 2:
                printf("Enter value to be inserted: ");
                scanf("%d", &val);
                root = insert(root, val); break;
            case 3:
                printf("Enter value to be deleted: ");
                scanf("%d", &val);
                root = delete(root, val); break;
            case 4:
                printf("Enter value to be searched: ");
                scanf("%d", &val);
                if(search(root, val)) printf("%d found\n", val);
                else printf("%d not found\n", val); break;
            default: printf("Invalid choice\n"); break;
        }
    }
}

int search(node *root, int val) {
    if(root == NULL) return 0;
    else if(val < root->data) return search(root->left, val);
    else if(val > root->data) return search(root->right, val);
    else if(val == root->data) return 1;
}

node* create_node(int val) {
    node *temp = malloc(sizeof(node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 1;
    return temp;
}
int max(int a, int b) {
    return ((a > b) ? a : b);
}

int height(node *n) {
    if(n == NULL) return 0;
    else return n->height;
}

node* rotate_left(node *x) {
    node *y = x->right;
    node *y_left = y->left;
    y->left = x;
    x->right = y_left;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

node* rotate_right(node *x) {
    node *y = x->left;
    node *y_right = y->right;
    y->right = x;
    x->left = y_right;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

node* insert(node *root, int val) {
    if(root == NULL) return create_node(val);
    else if(val < root->data) root->left = insert(root->left, val);
    else if(val > root->data) root->right = insert(root->right, val);
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if(balance < -1) {
        if(val < root->right->data) root->right = rotate_right(root->right);
        return rotate_left(root);
    } else if(balance > 1) {
        if(val > root->left->data) root->left = rotate_left(root->left);
        return rotate_right(root);
    } else return root;
}

node* min_succesor(node *root) {
    node *temp = root->right;
    while(temp->left != NULL) temp = temp->left;
    return temp;
}

node* delete(node *root, int val) {
    if(root == NULL) return root;
    else if(val < root->data) root->left = delete(root->left, val);
    else if(val > root->data) root->right = delete(root->right, val);
    else if(val == root->data) {
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if(root->left != NULL && root->right == NULL) {
            node *temp = root->left;
            free(root);
            root = temp;
        } else if(root->left == NULL && root->right != NULL) {
            node *temp = root->right;
            free(root);
            root = temp;
        } else {
            node *ms  = min_succesor(root);
            root->data = ms->data;
            root->right = delete(root->right, ms->data);
        }
    }
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = height(root->left) - height(root->right);
    if(balance < -1) {
        int right_balance = height(root->right->left) - height(root->right->right);
        if(right_balance > 0) root->right = rotate_right(root->right);
        return rotate_left(root);
    } else if(balance > 1) {
        int left_balance = height(root->left->left) - height(root->left->right);
        if(left_balance < 0) root->left = rotate_left(root->left);
        return rotate_right(root);
    } else return root;
}

void display(node *root) {
    static int depth = 0;
    if(root == NULL) return;
    else {
        for(int i = 0; i < depth-1; i++) printf("|     ");
        if(depth > 0) printf("|---->");
        printf("%d\n", root->data);
    }
    depth++;
    display(root->left);
    display(root->right);
    depth--;
}