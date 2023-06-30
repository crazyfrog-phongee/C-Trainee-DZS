#ifndef STACK_LLIST_H
#define STACK_LLIST_H

#define STACK_EMPTY -1

typedef struct llist_node llist_node_t;

/**
 * llist_t is a struct containing at least a head pointer to the TOP of the STACK;
 */
typedef struct llist llist_t;

/**
 * Service Functions
 */

llist_t *stack_create(llist_t *stack);
int is_empty_stack(const llist_t *stack);
void stack_push(llist_t *stack, int data);
int stack_pop(llist_t *stack);
int stack_peek(const llist_t *stack);
int stack_size(const llist_t *stack);
void stack_free(llist_t *stack);
void print_stack(const llist_t *stack);

#endif
