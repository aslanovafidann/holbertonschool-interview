#include "binary_trees.h"

/**
 * get_insert_parent - Finds the parent node where the next node should be
 * inserted in level-order.
 * @root: Pointer to the root of the heap.
 *
 * Return: Pointer to the parent node.
 */
heap_t *get_insert_parent(heap_t *root)
{
	heap_t *queue[1024];
	int head = 0, tail = 0;

	if (!root)
		return (NULL);

	queue[tail++] = root;

	while (head < tail)
	{
		heap_t *current = queue[head++];

		if (!current->left || !current->right)
			return (current);

		queue[tail++] = current->left;
		queue[tail++] = current->right;
	}

	return (NULL);
}

/**
 * heap_insert - Inserts a value into a Max Binary Heap.
 * @root: A double pointer to the root node of the Heap.
 * @value: The value to store in the node to be inserted.
 *
 * Return: A pointer to the inserted node, or NULL on failure.
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node, *parent;
	int temp;

	if (!root)
		return (NULL);

	/* If tree is empty, create root node */
	if (!*root)
	{
		*root = binary_tree_node(NULL, value);
		return (*root);
	}

	/* Find parent node for insertion point */
	parent = get_insert_parent(*root);
	new_node = binary_tree_node(parent, value);
	if (!new_node)
		return (NULL);

	/* Attach to left if empty, otherwise right */
	if (!parent->left)
		parent->left = new_node;
	else
		parent->right = new_node;

	/* Bubble up / Max Heapify up */
	while (new_node->parent && new_node->n > new_node->parent->n)
	{
		temp = new_node->n;
		new_node->n = new_node->parent->n;
		new_node->parent->n = temp;
		new_node = new_node->parent;
	}

	return (new_node);
}
