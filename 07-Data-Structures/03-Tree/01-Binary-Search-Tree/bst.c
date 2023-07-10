#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

tree_node_t *create_node(int item)
{
    tree_node_t *dummy = (tree_node_t *)malloc(sizeof(tree_node_t));
    dummy->item = item;
    dummy->left = NULL;
    dummy->right = NULL;

    return dummy;
}

void bst_insert(tree_node_t *node, int item)
{
    /* Return a new node (creating root) if the tree is empty */
    if (NULL == node)
    {
        node = create_node(item);
        return;
    }

    /* Trarverse to the right place and insert the node */
    if (item < node->item)
    {
        bst_insert(node->left, item);
    }
    else
    {
        bst_insert(node->right, item);
    }

    return;
}

void bst_free(tree_node_t *root)
{
    if (NULL == root)
    {
        return;
    }

    bst_free(root->left);
    bst_free(root->right);
    free(root);

    return;
}

void bst_print(tree_node_t *root, int is_right, int offset)
{
    if (root == NULL)
        return;

    offset += 7;

    bst_print(root->right, 1, offset);

    for (int i = 7; i < offset; i++)
    {
        printf(" ");
    }

    if (is_right)
    {
        printf(" /");
    }
    else
    {
        printf(" \\");
    }

    printf("----- ");
    printf("%d\n", root->item);

    bst_print(root->left, 0, offset);

    return;
}

void process(int item)
{
    printf("%d ", item);
}

void bst_print_by_pre_order(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    process(root->item);
    bst_print_by_pre_order(root->left);
    bst_print_by_pre_order(root->right);
}

void bst_print_by_in_order(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    bst_print_by_in_order(root->left);
    process(root->item);
    bst_print_by_in_order(root->right);
}

void bst_print_by_post_order(tree_node_t *root)
{
    if (root == NULL)
    {
        return;
    }

    bst_print_by_post_order(root->left);
    bst_print_by_post_order(root->right);
    process(root->item);
}
