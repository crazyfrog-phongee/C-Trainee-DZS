#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

#include <inttypes.h>

int main(int argc, char const *argv[])
{
    int i = 5, x = 10;
    pid_t child_pid;

    child_pid = fork();
    switch (child_pid)
    {
    case -1:
        /* Handle error */
        break;

    case 0:
        /* Perform actions specific to child */
        {
            i++;
            printf("Child (PID = %d): i = %d, &i = %p, &x = %p\n", getpid(), i, &i, &x);
            exit(EXIT_SUCCESS);
        }

    default:
        /* Perform actions specific to parent */
        {
            sleep(1);
            printf("Parent (PID = %d): i = %d, &i = %p, &x = %p\n", getpid(), i, &i, &x);
        }
    }

    return 0;
}
