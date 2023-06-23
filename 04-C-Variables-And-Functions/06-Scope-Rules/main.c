#include <stdio.h>

/* Declare, Definite and Initialize a global variable */
int g_number = 5;

/* Extern variables */
extern int var; /* Declaration: it hasn’t been defined yet, so no memory allocation for var so far */

void display(void)
{
    printf("%d\n", g_number);
}

void display_extern_var(void) /* Definition */
{
    printf("Address allocated for var: %p and value: %d\n", &var, var);
}

int main(int argc, char const *argv[])
{
    /* Declare, Definite and Initialize a local variable */
    int number = 10;

    printf("Value of local variable: %d\n", number);
    
    display_extern_var();

    printf("Before changing within main: ");
    display();

    /* Changing value of global variable from main function */
    printf("After changing within main: ");
    g_number = 10;
    display();
    
    return 0;
}
