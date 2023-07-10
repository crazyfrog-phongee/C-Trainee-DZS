#include <stdio.h>

#include "user_app.h"

stack_t peg[NUM_PEGS];

int main(int argc, char const *argv[])
{
    int is_win_game = 0;
    int move_value;

    init_game(peg);

    while (0 == is_win_game)
    {
        move_value = user_pop(peg);
        user_push(peg, move_value);
        is_win_game = check_win_game(peg);
        display_pegs(peg);
    }

    end_game();
    
    return 0;
}