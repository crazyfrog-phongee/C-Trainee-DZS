#include <stdio.h>

int var; /* Definition */

extern void display_extern_var(void); /* Declaration: it hasn’t been defined yet, so no memory allocation for var so far */