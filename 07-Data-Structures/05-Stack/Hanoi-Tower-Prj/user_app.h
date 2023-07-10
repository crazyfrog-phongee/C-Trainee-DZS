#ifndef USER_APP_H
#define USER_APP_H

#include "lib/stack_arr.h"

#define NUM_PEGS    3

void init_game(stack_t *peg);
void display_pegs(const stack_t *peg);
int user_pop(stack_t *peg);
void user_push(stack_t *peg, int item);
int check_win_game(const stack_t *peg);
void end_game(void);

#endif