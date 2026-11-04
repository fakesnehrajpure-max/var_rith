/* AVL TREE - MIXED SCENARIO
   A company inserts employee IDs that arrive ALREADY SORTED (1, 2, 3 ... N).
   1) Insert them into a plain BST and an AVL tree.
   2) Compare the heights of both trees and explain why the plain BST is slow.
   3) Count how many rotations the AVL tree performed. */

#include <stdio.h>
#include <stdlib.h>

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
void update_height(node *root);
void rotate_right(node **root, int *rotations);
void rotate_left(node **root, int *rotations);
void avl_insert(node **root, int value, int *rotations);
void bst_insert(node **root, int value);
int bst_height(node *root);
void free_tree(node *root);

int main()
{
	node *bst = NULL, *avl = NULL;
	int n, rotations = 0;
	printf("give N (IDs 1..N inserted in order):\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid N\n");
		return 1;
	}
	for(int i = 1; i <= n; i++)
	{
		bst_insert(&bst, i);
		avl_insert(&avl, i, &rotations);
	}
	printf("plain BST height: %d (a straight line, search is O(n))\n", bst_height(bst));
	printf("AVL height: %d (about log2(N), search is O(log n))\n", height(avl));
	printf("rotations done by AVL: %d\n", rotations);

	while(bst != NULL)			/* sorted input: every BST node has only a right child */
	{
		node *temp = bst;
		bst = bst->right;
		free(temp);
	}
	free_tree(avl);
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

void update_height(node *root)
{
	int hl = height(root->left), hr = height(root->right);
	if(hl > hr)
		root->height = hl + 1;
	else
		root->height = hr + 1;
}

void rotate_right(node **root, int *rotations)
{
	node *x = (*root)->left;
	(*root)->left = x->right;
	x->right = *root;
	update_height(*root);
	update_height(x);
	*root = x;
	(*rotations)++;
}

void rotate_left(node **root, int *rotations)
{
	node *y = (*root)->right;
	(*root)->right = y->left;
	y->left = *root;
	update_height(*root);
	update_height(y);
	*root = y;
	(*rotations)++;
}

void avl_insert(node **root, int value, int *rotations)
{
	if(*root == NULL)
	{
		*root = createNode(value);
		return;
	}
	if(value < (*root)->data)
		avl_insert(&(*root)->left, value, rotations);
	else
		avl_insert(&(*root)->right, value, rotations);

	update_height(*root);
	int bf = height((*root)->left) - height((*root)->right);
	if(bf > 1)
	{
		if(value > (*root)->left->data)		/* LR */
			rotate_left(&(*root)->left, rotations);
		rotate_right(root, rotations);		/* LL */
	}
	else if(bf < -1)
	{
		if(value < (*root)->right->data)	/* RL */
			rotate_right(&(*root)->right, rotations);
		rotate_left(root, rotations);		/* RR */
	}
}

/* iterative, so a long sorted chain does not overflow the call stack */
void bst_insert(node **root, int value)
{
	node *new_node = createNode(value);
	if(new_node == NULL)
		return;
	if(*root == NULL)
	{
		*root = new_node;
		return;
	}
	node *r = *root;
	while(1)
	{
		if(value < r->data)
		{
			if(r->left == NULL)
			{
				r->left = new_node;
				return;
			}
			r = r->left;
		}
		else
		{
			if(r->right == NULL)
			{
				r->right = new_node;
				return;
			}
			r = r->right;
		}
	}
}

/* sorted input makes a right chain, so walk it instead of recursing */
int bst_height(node *root)
{
	int h = 0;
	for(node *r = root; r != NULL; r = r->right)
		h++;
	return h;
}

void free_tree(node *root)
{
	if(root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
