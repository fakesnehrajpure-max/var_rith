/* Day 7 Q1
   Implement an AVL tree with the following functions:
   Insert node
   Balancing
   Search node
   Delete node */

#include <stdio.h>
#include <stdlib.h>
#define EXIT 0

typedef struct node
{
	int data;
	int height;
	struct node *left;
	struct node *right;
}node;

/****function declarations****/
node *createNode(int value);
int height(node *root);
int balance_factor(node *root);
void update_height(node *root);
void rotate_right(node **root);
void rotate_left(node **root);
void rebalance(node **root);
void insertNode(node **root, int value);
void searchNode(node *root, int value);
void deleteNode(node **root, int value);
void inorder(node *root);
void preorder(node *root);
void free_tree(node *root);

int main()
{
	node *root = NULL;
	int choice, value;

	do
	{
		printf("\n0.exit\n1.insert\n2.search\n3.delete\n4.display\n");
		printf("give the choice:\t");
		scanf("%d", &choice);

		switch(choice)
		{
			case 1:
				printf("give value:\t");
				scanf("%d", &value);
				insertNode(&root, value);
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
				if(root == NULL)
				{
					printf("tree is empty\n");
					break;
				}
				printf("inorder (value:bf): ");
				inorder(root);
				printf("\npreorder: ");
				preorder(root);
				printf("\nroot: %d\n", root->data);
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
	new_node->height = 1;
	new_node->left = NULL;
	new_node->right = NULL;
	return new_node;
}

int height(node *root)
{
	if(root == NULL)
		return 0;
	else
		return root->height;
}

/* BF = height(left) - height(right), must stay in -1, 0, +1 */
int balance_factor(node *root)
{
	if(root == NULL)
		return 0;
	else
		return height(root->left) - height(root->right);
}

void update_height(node *root)
{
	int hl = height(root->left), hr = height(root->right);
	if(hl > hr)
		root->height = hl + 1;
	else
		root->height = hr + 1;
}

/* LL fix: left child becomes the new root */
void rotate_right(node **root)
{
	node *x = (*root)->left;
	(*root)->left = x->right;
	x->right = *root;
	update_height(*root);
	update_height(x);
	*root = x;
}

/* RR fix: right child becomes the new root */
void rotate_left(node **root)
{
	node *y = (*root)->right;
	(*root)->right = y->left;
	y->left = *root;
	update_height(*root);
	update_height(y);
	*root = y;
}

void rebalance(node **root)
{
	update_height(*root);
	int bf = balance_factor(*root);
	if(bf > 1)					/* left heavy */
	{
		if(balance_factor((*root)->left) < 0)	/* LR: first left-rotate the child */
			rotate_left(&(*root)->left);
		rotate_right(root);			/* LL */
	}
	else if(bf < -1)				/* right heavy */
	{
		if(balance_factor((*root)->right) > 0)	/* RL: first right-rotate the child */
			rotate_right(&(*root)->right);
		rotate_left(root);			/* RR */
	}
}

void insertNode(node **root, int value)
{
	if(*root == NULL)
	{
		*root = createNode(value);
		return;
	}
	if(value < (*root)->data)
		insertNode(&(*root)->left, value);
	else if(value > (*root)->data)
		insertNode(&(*root)->right, value);
	else
	{
		printf("duplicate %d ignored\n", value);
		return;
	}
	rebalance(root);			/* fix balance on the way back up */
}

void searchNode(node *root, int value)
{
	node *r = root;
	while(r != NULL)
	{
		if(value == r->data)
		{
			printf("%d found\n", value);
			return;
		}
		else if(value < r->data)
			r = r->left;
		else
			r = r->right;
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
		deleteNode(&(*root)->left, value);
	else if(value > (*root)->data)
		deleteNode(&(*root)->right, value);
	else
	{
		node *temp = *root;
		if((*root)->left == NULL)
		{
			*root = (*root)->right;
			free(temp);
		}
		else if((*root)->right == NULL)
		{
			*root = (*root)->left;
			free(temp);
		}
		else
		{
			node *succ = (*root)->right;
			while(succ->left != NULL)
				succ = succ->left;
			(*root)->data = succ->data;
			deleteNode(&(*root)->right, succ->data);
		}
	}
	if(*root != NULL)
		rebalance(root);
}

void inorder(node *root)
{
	if(root == NULL)
		return;
	inorder(root->left);
	printf("%d:%d ", root->data, balance_factor(root));
	inorder(root->right);
}

void preorder(node *root)
{
	if(root == NULL)
		return;
	printf("%d ", root->data);
	preorder(root->left);
	preorder(root->right);
}

void free_tree(node *root)
{
	if(root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
