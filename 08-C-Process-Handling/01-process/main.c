#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>       /* Need for functions such as fork() */
#include <sys/resource.h> /* Need for functions such as getrlimit() */

extern char **environ;
static int idata = 111; /* Allocated in data segment */

rlim_t max_processes_for_current_user(void)
{
    struct rlimit rlp;
    getrlimit(RLIMIT_NPROC, &rlp);

    return rlp.rlim_max;
}

int main(int argc, char const *argv[])
{
    printf("Hello from HelloDZS program\n");
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    printf("\nCommand-Line Arguments:\n");
    for (int j = 0; j < argc; j++)
    {
        printf("argv[%d] = %s\n", j, argv[j]);
    }

    // while (1);

    // printf("\nEnvironment List:\n");
    // for (char **ep = environ; NULL != *ep; ep++)
    // {
    //     puts(*ep);
    // }

    // printf("Get the limit on the number of extant process for the real user ID of the calling process: %ld\n", max_processes_for_current_user());

    // pid_t child_pid;
    // int istack = 222; /* Allocated in stack segment */

    // switch (child_pid = fork())
    // {
    // case -1:
    //     /* Handle error */
    //     break;

    // case 0:
    //     /* Perform actions specific to child */
    //     printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());
    //     istack *= 3;
    //     break;

    // default:
    //     /* Perform actions specific to parent */
    //     sleep(3);
    //     break;
    // }

    // /* Both parent and child come here */
    // printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(),
    //        (child_pid == 0) ? "(child) " : "(parent)", idata, istack);

    return 0;
}
