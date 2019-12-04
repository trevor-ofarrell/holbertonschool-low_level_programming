#include "binary_trees.h"

size_t _binary_tree_height(const binary_tree_t *tree)
{
  int rightdepth, leftdepth;
  
  if (tree == NULL)
    return (0);
  else
    {
      rightdepth = _binary_tree_height(tree->right);
      leftdepth = _binary_tree_height(tree->left);

      if (rightdepth < leftdepth)
	return (leftdepth + 1);
      else
	return (rightdepth + 1);
    }
}

size_t binary_tree_height(const binary_tree_t *tree)
{
  if (!tree)
    return (0);
  
  return (_binary_tree_height(tree) - 1);
}
