#ifndef STACK_LLIST_H
#define STACK_LLIST_H

typedef struct llist_node llist_node_t;
typedef struct llist llist_t;

/**
 * Service Functions
 */

llist_t *stack_create(llist_t *stack);
void stack_push(llist_t *stack, int data);
void print_stack(const llist_t *stack);

#endif
