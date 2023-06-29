#ifndef STACK_H_
#define STACK_H_

#define STACK_SIZE  10
#define STACK_SUCCESS 0
#define STACK_FAILURE -1

typedef struct stack stack_t;

struct stack
{
    int stack[STACK_SIZE];
    int top;
};

/**
 * Service Functions
*/
int init_stack(stack_t *s);
int is_full(const stack_t *s);
int is_empty(const stack_t *s);
int push(stack_t *s, int data);
int pop(stack_t *s);
int peek(const stack_t *s);
void print_stack(const stack_t *s);

#endif 