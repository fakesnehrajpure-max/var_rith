/* Day 6 Q1
   WAP to create a Binary Search Tree.
   a) Implement addNode() which adds a new node in the tree on the LHS or RHS sub-tree
      depending on whether its value is smaller or greater than the root
   b) Implement functions to display Pre-order, In-order, Post-order traversals
   c) Implement a function to search a node with a user defined value in the tree
   d) Implement a function to delete a user-defined node from the tree
   e) Create a menu driven program with options:
      Add, Search, Delete, PreOrder, Inorder, PostOrder, EXIT */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct node
{
	int data;
	struct node *left;
	struct node *right;
}node;

/****function declarations****/
node *createNode(int value);
void addNode(node **root, int value);
void searchNode(node *root, int value);
void deleteNode(node **root, int value);
void preorder(node *root);
void inorder(node *root);
void postorder(node *root);
void free_tree(node *root);

int main()
{
	node *root = NULL;
	int choice, value;

	do
	{
		printf("\n0.exit\n1.add\n2.search\n3.delete\n4.preorder\n5.inorder\n6.postorder\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				addNode(&root, value);
				break;
			case 2:
				printf("give value:\t");
				scanf("%d", &value);
				searchNode(root, value);
				break;
			case 3:
				printf("give value:\t");
				scanf("%d", &value);
				deleteNode(&root, value);
				break;
			case 4:
				if(root == NULL) printf("tree is empty");
				preorder(root);
				printf("\n");
				break;
			case 5:
				if(root == NULL) printf("tree is empty");
				inorder(root);
				printf("\n");
				break;
			case 6:
				if(root == NULL) printf("tree is empty");
				postorder(root);
				printf("\n");
				break;
			case EXIT: printf("exiting\n"); break;
			default: printf("invalid choice\n");
		}
	}while(choice != EXIT);

	free_tree(root);
	return 0;
}

node *createNode(int value)
{
	node *new_node = malloc(sizeof(node));
	if(new_node == NULL)
	{
		printf("malloc failed");
		return NULL;
	}
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

/* smaller -> left, bigger -> right, until an empty spot */
void addNode(node **root, int value)
{
	if(*root == NULL)
	{
		*root = createNode(value);
		return;
	}
	if(value < (*root)->data)
		addNode(&(*root)->left, value);
	else if(value > (*root)->data)
		addNode(&(*root)->right, value);
	else
		printf("duplicate %d ignored\n", value);
}

void searchNode(node *root, int value)
{
	int level = 0;
	node *r = root;
	while(r != NULL)
	{
		if(value == r->data)
		{
			printf("%d found at level %d\n", value, level);
			return;
		}
		else if(value < r->data)
			r = r->left;
		else
			r = r->right;
		level++;
	}
	printf("%d not found\n", value);
}

void deleteNode(node **root, int value)
{
	if(*root == NULL)
	{
		printf("%d not found\n", value);
		return;
	}
	if(value < (*root)->data)
	{
		deleteNode(&(*root)->left, value);
		return;
	}
	if(value > (*root)->data)
	{
		deleteNode(&(*root)->right, value);
		return;
	}

	node *temp = *root;
	if((*root)->left == NULL)		/* case 1 and 2: leaf or only right child */
	{
		*root = (*root)->right;
		free(temp);
	}
	else if((*root)->right == NULL)		/* case 2: only left child */
	{
		*root = (*root)->left;
		free(temp);
	}
	else					/* case 3: two children */
	{
		node *succ = (*root)->right;	/* inorder successor: smallest in right subtree */
		while(succ->left != NULL)
			succ = succ->left;
		(*root)->data = succ->data;	/* copy successor's value in */
		deleteNode(&(*root)->right, succ->data);	/* then delete the successor */
	}
}

void preorder(node *root)
{
	if(root == NULL)
		return;
	printf("%d ", root->data);		/* root first */
	preorder(root->left);
	preorder(root->right);
}

void inorder(node *root)
{
	if(root == NULL)
		return;
	inorder(root->left);
	printf("%d ", root->data);		/* root in the middle: sorted */
	inorder(root->right);
}

void postorder(node *root)
{
	if(root == NULL)
		return;
	postorder(root->left);
	postorder(root->right);
	printf("%d ", root->data);		/* root last */
}

void free_tree(node *root)
{
	if(root == NULL)
		return;
	free_tree(root->left);			/* postorder: children before parent */
	free_tree(root->right);
	free(root);
}
