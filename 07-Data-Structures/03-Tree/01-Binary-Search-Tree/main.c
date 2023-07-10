#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main(int argc, char const *argv[])
{
    tree_node_t *root = NULL;
    root = (tree_node_t *) malloc(sizeof(tree_node_t));
    root->item = 8;
    // bst_insert(root, 8);
    bst_insert(root, 3);
    bst_insert(root, 1); 
    bst_insert(root, 5);
    bst_insert(root, 4);
    bst_insert(root, 6);
    bst_insert(root, 10);
    bst_insert(root, 9);
    bst_insert(root, 15);

    bst_print(root, 0, 3);

    printf("Preorder Traversal Tree: ");
    bst_print_by_pre_order(root);
    printf("\n");

    printf("Inorder Traversal Tree: ");
    bst_print_by_in_order(root);
    printf("\n");

    printf("Postorder Traversal Tree: ");
    bst_print_by_post_order(root);
    printf("\n");

    bst_free(root);
    
    return 0;
}
