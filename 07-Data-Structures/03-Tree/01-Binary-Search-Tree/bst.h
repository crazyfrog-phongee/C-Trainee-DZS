#ifndef BST_H_
#define BST_H_

#define BST_SUCCESS 0
#define BST_FAILED  -1

typedef struct tree_node tree_node_t;

struct tree_node
{
    int item;
    tree_node_t *left;
    tree_node_t *right;
};

tree_node_t *create_node(int item);
void bst_insert(tree_node_t *node, int item);
void bst_free(tree_node_t *root);
void process(int item);
void bst_print_by_pre_order(tree_node_t *root);
void bst_print_by_in_order(tree_node_t *root);
void bst_print_by_post_order(tree_node_t *root);
void bst_print(tree_node_t *root, int is_right, int offset);

#endif