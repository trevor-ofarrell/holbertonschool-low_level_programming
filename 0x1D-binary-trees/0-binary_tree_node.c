#include "binary_trees.h"
/**
 * binary_tree_node - create parent node of binary tree
 * @parent: first node
 * @value: int
 *
 * Return: pointer to node
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{

  binary_tree_t *new = (binary_tree_t*) malloc(sizeof(binary_tree_t));

  new->parent = parent;
  new->n = value;
  new->left = NULL;
  new->right = NULL;

  return (new);
}
