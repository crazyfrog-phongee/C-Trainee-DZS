#include <stdio.h>

int Static[5];

int main(int argc, char const *argv[])
{
    int Stack[5];
    int Arr[10];

    Static[5] = 0; /* Error - Static[0] to Static[4] exist, Static[5] is out of bounds */
    Stack[5] = 1000;  /* Error - Stack[0] to Stack[4] exist, Stack[5] is out of bounds */
    Arr[10] = 1000;
    return 0;
}
