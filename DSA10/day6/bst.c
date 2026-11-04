#include <stdio.h>
#include <stdlib.h>
typedef struct node_internal {
    int data;
    struct node_internal *left;
    struct node_internal *right;
} node;

node *createNode(int data);
node *addNode(node *root, int data);
void preorder(node *root);
void inorder(node *root);
void postorder(node *root);
void search(node *root, int key);
node *delete(node *root, int key);
int min_succesor(node *root);
void display(node *root);
void print_n_tabs(int n);
void print_branch(int n);
int main() {
    node *root = NULL;
    int choice, data;
    printf("0: exit\n1: display\n2: add node\n3: delete node\n4: search node\n"
           "5: pre-order traversal\n6: in-order traversal\n7: post-order traversal\n");
    while(1) {
        printf("\nEnter choice: \n");
        scanf("%d", &choice);
        switch(choice) {
            case 0:
               exit(0); break;
            case 1:
                display(root);
                break;
            case 2:
                printf("Enter value of node to be added: ");
                scanf("%d", &data);
                root = addNode(root, data);
                break;
            case 3:
                printf("Enter value of node to be deleted: ");
                scanf("%d", &data);
                root = delete(root, data);
                break;
            case 4:
                printf("Enter value of node to be searched: ");
                scanf("%d", &data);
                search(root, data);
                break;
            case 5:
                printf("Pre-order traversal:\n");
                preorder(root);
                break;
            case 6:
                printf("In-order traversal:\n");
                inorder(root);
                break;
            case 7:
                printf("Post-order traversal:\n");
                postorder(root);
                break;
        }
    }
    return 0;

}

node *createNode(int data) {
    node *temp = malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

node *addNode(node *root, int data) {
    if(root == NULL) {
        node *temp = createNode(data);
        return temp;
    } else if(data < root->data) root->left = addNode(root->left, data);
    else if(data > root->data) root->right = addNode(root->right, data);
    return root;
}

void preorder(node *root) {
    if(root == NULL) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(node *root) {
    if(root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);

}
void postorder(node *root) {
    if(root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void search(node *root, int key) {
    if(root == NULL) printf("%d not found in the tree\n", key);
    else if(key == root->data) printf("%d found in the tree\n", key);
    else if(key < root->data) search(root->left, key);
    else if(key > root->data) search(root->right, key);
}

node *delete(node *root, int key) {
    if(root == NULL) {
        printf("%d not found in the tree\n", key);
        return root;
    } else if(key == root->data) {
        if(root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        } else if(root->left == NULL && root->right != NULL) {
            node *temp = root->right;
            free(root);
            return temp;
        } else if(root->left != NULL && root->right == NULL) {
            node *temp = root->left;
            free(root);
            return temp;
        } else {
            // root->data = min_succesor(root);
            // root->right = delete(root->right, root->data);
            // return root;
            node *temp = root->right;
            node *temp2 = temp;
            while(temp2->left != NULL) temp2 = temp2->left;
            temp2->left = root->left;
            free(root);
            return temp;
        }
    } else {
        if(key < root->data) root->left = delete(root->left, key);
        if(key > root->data) root->right = delete(root->right, key);
        return root;
    }
}

int min_succesor(node *root) {
    node *temp = root->right;
    while(temp->left != NULL) temp = temp->left;
    return temp->data;
}

void display(node *root) {
    static int depth = 0;
    if(root == NULL) {
        return;
    } else {
        for(int i = 0; i < depth-1; i++) printf("|     ");
        if(depth > 0) printf("|---->");
        printf("%d\n", root->data);
    }
    depth++;
    display(root->left);
    display(root->right);
    depth--;
}