/* BINARY SEARCH TREE - MIXED SCENARIO
   A library stores book IDs in a BST.
   1) Print all book IDs in a given range [low, high] without visiting every node.
   2) Find the height of the tree and count the leaf nodes.
   3) Find the k-th smallest book ID.
   4) Find the lowest common ancestor (shelf section) of two book IDs.
   5) Print the tree level by level (uses a queue). */

#include <stdio.h>
#include <stdlib.h>
#define QSIZE 100

typedef struct node
{
	int id;
	struct node *left;
	struct node *right;
}node;

/****function declarations****/
void addNode(node **root, int id);
void range(node *root, int low, int high);
int height(node *root);
int leaves(node *root);
void kth_smallest(node *root, int *k);
void lca(node *root, int a, int b);
void level_order(node *root);
void free_tree(node *root);

int main()
{
	node *root = NULL;
	int n, id, low, high, k, a, b;
	printf("give number of books:\t");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("invalid count\n");
		return 1;
	}
	printf("give %d book IDs:\t", n);
	for(int i = 0; i < n; i++)
	{
		scanf("%d", &id);
		addNode(&root, id);
	}

	printf("give range low high:\t");
	scanf("%d %d", &low, &high);
	printf("in range: ");
	range(root, low, high);
	printf("\nheight %d, leaves %d\n", height(root), leaves(root));

	printf("give k:\t");
	scanf("%d", &k);
	kth_smallest(root, &k);
	if(k > 0)
		printf("tree has fewer books than k\n");

	printf("give two IDs for LCA:\t");
	scanf("%d %d", &a, &b);
	lca(root, a, b);

	printf("level order:\n");
	level_order(root);
	free_tree(root);
	return 0;
}

void addNode(node **root, int id)
{
	if(*root == NULL)
	{
		*root = malloc(sizeof(node));
		if(*root == NULL)
		{
			printf("malloc failed");
			return;
		}
		(*root)->id = id;
		(*root)->left = NULL;
		(*root)->right = NULL;
		return;
	}
	if(id < (*root)->id)
		addNode(&(*root)->left, id);
	else if(id > (*root)->id)
		addNode(&(*root)->right, id);
}

/* inorder, but skip a side that cannot hold values in range */
void range(node *root, int low, int high)
{
	if(root == NULL)
		return;
	if(root->id > low)
		range(root->left, low, high);
	if(root->id >= low && root->id <= high)
		printf("%d ", root->id);
	if(root->id < high)
		range(root->right, low, high);
}

int height(node *root)
{
	if(root == NULL)
		return 0;
	int hl = height(root->left), hr = height(root->right);
	if(hl > hr)
		return hl + 1;
	else
		return hr + 1;
}

int leaves(node *root)
{
	if(root == NULL)
		return 0;
	if(root->left == NULL && root->right == NULL)
		return 1;
	return leaves(root->left) + leaves(root->right);
}

/* inorder visits in sorted order: count down k, print when it hits 0 */
void kth_smallest(node *root, int *k)
{
	if(root == NULL || *k <= 0)
		return;
	kth_smallest(root->left, k);
	if(*k <= 0)
		return;
	(*k)--;
	if(*k == 0)
	{
		printf("k-th smallest: %d\n", root->id);
		return;
	}
	kth_smallest(root->right, k);
}

/* walk down while both IDs are on the same side */
void lca(node *root, int a, int b)
{
	node *r = root;
	while(r != NULL)
	{
		if(a < r->id && b < r->id)
			r = r->left;
		else if(a > r->id && b > r->id)
			r = r->right;
		else
		{
			printf("LCA: %d\n", r->id);
			return;
		}
	}
	printf("no LCA\n");
}

void level_order(node *root)
{
	if(root == NULL)
		return;
	node *queue[QSIZE];
	node **front = queue, **rear = queue;
	*rear++ = root;
	while(front < rear)
	{
		node **level_end = rear;		/* everything before this is one level */
		while(front < level_end)
		{
			node *x = *front++;
			printf("%d ", x->id);
			if(x->left != NULL)
				*rear++ = x->left;
			if(x->right != NULL)
				*rear++ = x->right;
		}
		printf("\n");
	}
}

void free_tree(node *root)
{
	if(root == NULL)
		return;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}
