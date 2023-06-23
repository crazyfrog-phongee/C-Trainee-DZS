#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned char a = 10;
    if (a = 1)
    {
        printf("%d\n", a);
    }
    int count = 1;
    switch (count)
    {
        default:
        {
            printf("Default\n");
            break;
        }
        case 1:
        {
            printf("One\n");
        }
        case 2:
        {
            printf("Two\n");
            break;
        }
        case 3:
        {
            printf("Three\n");
            break;
        }
        case 4:
        {
            printf("Four\n");
            break;
        }
    }
    
    return 0;
}
