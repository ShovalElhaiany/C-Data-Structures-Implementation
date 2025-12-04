/*****************************************
 * date: Tue Jun 17 2025                 *
 * name: Shoval Elhaiany                 *
 * code reviewer: John Doe               *
 *****************************************/

#include <stdlib.h> /* malloc, free */
#include <assert.h> /* assert */
#include "../include/avl.h"

/* node definition */
struct node_s
{
	node_t* side[2];
	void* data;
	size_t height;
};

/* tree definition */
struct avl_s
{
	node_t* root;
	avl_cmp_t cmp_func;
};

/* ======================== HELPER FUNCS SIGNATURES ======================== */

static size_t Height(node_t* node);
static void UpdateHeight(node_t* node);
static int BalanceFactor(node_t* node);
static node_t* Rotate(node_t* root, int dir);
static node_t* Rebalance(node_t* node);
static node_t* NewNode(void* data);
static node_t* InsertRec(node_t* root, void* data, avl_cmp_t cmp, int* status);
static node_t* MinNode(node_t* node);
static node_t* RemoveRec(node_t* root, const void* data, avl_cmp_t cmnodep);
static size_t CountRec(const node_t* node);
static int ForEachRec(node_t* node, avl_op_t op, void* arg);
static void* FindRec(const node_t* node, const void* data, avl_cmp_t cmp);
static void DestroyRec(node_t* node);

/* ========================================================================= */

/* ========================================================================
 *                                                                        *
 *                                API FUNCS                               *
 *                                                                        *
 ======================================================================== */

/* ================================= CREATE ================================= */

avl_t* AVLCreate(avl_cmp_t sorting_method)
{
	avl_t* tree = malloc(sizeof(avl_t));
	if (!tree)
		return NULL;

	if (!sorting_method)
		return NULL;

	tree->root = NULL;
	tree->cmp_func = sorting_method;
	return tree;
}

/* ================================ DESTROY ================================ */

void AVLDestroy(avl_t* tree)
{
	if (!tree)
		return;
	DestroyRec(tree->root);
	free(tree);
}

/* ================================= COUNT ================================= */

size_t AVLCount(const avl_t* tree)
{
	if (!tree)
		return 0;
	return CountRec(tree->root);
}

/* ================================ ISEMPTY ================================ */

int AVLIsEmpty(const avl_t* tree)
{
	assert(tree);
	return tree->root == NULL;
}

/* ================================= INSERT ================================= */

int AVLInsert(avl_t* tree, void* data)
{
	int status = 0;
	if (!tree || !tree->cmp_func)
		return 0;
	tree->root = InsertRec(tree->root, data, tree->cmp_func, &status);
	return status;
}

/* ================================= REMOVE ================================= */

void AVLRemove(avl_t* tree, const void* data)
{
	if (tree && tree->cmp_func)
		tree->root = RemoveRec(tree->root, data, tree->cmp_func);
}

/* ================================ FOREACH ================================ */

int AVLForEach(avl_t* tree, avl_op_t operation, void* arg)
{
	if (!tree || !operation)
		return 0;
	return ForEachRec(tree->root, operation, arg);
}

/* ================================== FIND ================================== */

void* AVLFind(const avl_t* tree, const void* data)
{
	if (!tree || !tree->cmp_func)
		return NULL;
	return FindRec(tree->root, data, tree->cmp_func);
}

/* ================================= HEIGHT ================================= */

size_t AVLHeight(const avl_t* tree)
{
	if (!tree)
		return 0;
	return Height(tree->root);
}

/* ========================================================================= */

/* ========================================================================
 *                                                                        *
 *                              HELPER FUNCS                              *
 *                                                                        *
 ======================================================================== */

/* ============================= DESTROY HELPER ============================= */

/* recursive destroy */
static void DestroyRec(node_t* node)
{
	if (!node)
		return;
	DestroyRec(node->side[0]);
	DestroyRec(node->side[1]);
	free(node);
}

/* ============================== COUNT HELPER ============================== */

/* recursive count */
static size_t CountRec(const node_t* node)
{
	if (!node)
		return 0;
	return 1 + CountRec(node->side[0]) + CountRec(node->side[1]);
}

/* ============================= INSERT HELPER ============================= */

/* recursive insert */
static node_t* InsertRec(node_t* root, void* data, avl_cmp_t cmp, int* status)
{
	int dir = 0;
	int cmp_res = 0;
	node_t* node = NULL;

	if (!root)
	{
		node = NewNode(data);
		if (!node)
			*status = -1;
		return node;
	}
	cmp_res = cmp(data, root->data);
	if (cmp_res == 0)
	{
		/* duplicates not supported */
		*status = -1;
		return root;
	}
	dir = cmp_res > 0;
	root->side[dir] = InsertRec(root->side[dir], data, cmp, status);
	if (*status)
		return root;
	return Rebalance(root);
}

/* ============================ GENERAL HELPERS ============================ */

/* create new node */
static node_t* NewNode(void* data)
{
	node_t* node = malloc(sizeof(node_t));
	if (!node)
		return NULL;
	node->side[0] = node->side[1] = NULL;
	node->data = data;
	node->height = 1;
	return node;
}

/* rebalance subtree */
static node_t* Rebalance(node_t* node)
{
	int bf = 0;
	UpdateHeight(node);
	bf = BalanceFactor(node);
	if (bf > 1)
	{
		/* right-heavy */
		if (BalanceFactor(node->side[1]) < 0)
		{
			/* RL case */
			node->side[1] = Rotate(node->side[1], 1);
		}
		/* RR case */
		return Rotate(node, 0);
	}
	if (bf < -1)
	{
		/* left-heavy */
		if (BalanceFactor(node->side[0]) > 0)
		{
			/* LR case */
			node->side[0] = Rotate(node->side[0], 0);
		}
		/* LL case */
		return Rotate(node, 1);
	}
	return node;
}

/* helper: update height of node from children */
static void UpdateHeight(node_t* node)
{
	size_t lh = Height(node->side[0]);
	size_t rh = Height(node->side[1]);
	node->height = (lh > rh ? lh : rh) + 1;
}

/* helper: get height of node (0 if null) */
static size_t Height(node_t* node)
{
	return node ? node->height : 0;
}

/* helper: get balance factor = right height - left height */
static int BalanceFactor(node_t* n)
{
	return (int) Height(n->side[1]) - (int) Height(n->side[0]);
}

/* single rotation: dir = 0 => right rotation; dir = 1 => left rotation */
static node_t* Rotate(node_t* root, int dir)
{
	int opp = dir ^ 1;
	node_t* pivot = root->side[opp];
	root->side[opp] = pivot->side[dir];
	pivot->side[dir] = root;
	UpdateHeight(root);
	UpdateHeight(pivot);
	return pivot;
}

/* recursive find minimum node in subtree */
static node_t* MinNode(node_t* node)
{
	while (node->side[0])
		node = node->side[0];
	return node;
}

/* recursive removal */
static node_t* RemoveRec(node_t* root, const void* data, avl_cmp_t cmp)
{
	int cmp_res = 0;
	node_t* child = NULL;
	node_t* succ = NULL;
	int dir = 0;

	if (!root)
		return NULL;
	cmp_res = cmp(data, root->data);
	if (cmp_res == 0)
	{
		/* remove this node */
		if (!root->side[0] || !root->side[1])
		{
			child = root->side[0] ? root->side[0] : root->side[1];
			free(root);
			return child;
		}
		/* two children: replace with successor */
		succ = MinNode(root->side[1]);
		root->data = succ->data;
		root->side[1] = RemoveRec(root->side[1], succ->data, cmp);
	}
	else
	{
		dir = cmp_res > 0;
		root->side[dir] = RemoveRec(root->side[dir], data, cmp);
	}
	return Rebalance(root);
}

/* recursive for-each (in-order) */
static int ForEachRec(node_t* node, avl_op_t op, void* arg)
{
	int res = 0;
	if (!node)
		return 0;
	res = ForEachRec(node->side[0], op, arg);
	if (res)
		return res;
	res = op(node->data, arg);
	if (res)
		return res;
	return ForEachRec(node->side[1], op, arg);
}

/* recursive find */
static void* FindRec(const node_t* node, const void* data, avl_cmp_t cmp)
{
	int cmp_res = 0;
	int dir = 0;

	if (!node)
		return NULL;
	cmp_res = cmp(data, node->data);
	if (cmp_res == 0)
		return node->data;
	dir = cmp_res > 0;
	return FindRec(node->side[dir], data, cmp);
}
