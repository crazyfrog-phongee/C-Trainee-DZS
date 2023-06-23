#include <stdio.h>

void checking(unsigned char *num)
{
    printf("Address: %p, Value: %d\n", num, *num);
}

int main(int argc, char const *argv[])
{
    int a = 10;
    /* Low addr: 0x01, High addr: 0x00 */
    unsigned char arr[2] = {0x01, 0x00};    
    unsigned short int x = *(unsigned short int *)arr;
    unsigned int y = *(unsigned int *)arr;

    printf("Address: %p, Value: %x\n", &x, x);
    printf("Address: %p, Value: %x\n", &y, y);

    return 0;
}
