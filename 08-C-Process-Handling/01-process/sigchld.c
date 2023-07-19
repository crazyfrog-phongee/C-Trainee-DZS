#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

void sig_handler(int signum);

int main(int argc, char const *argv[])
{
    pid_t child_pid;

    child_pid = fork();

    switch (child_pid)
    {
        case -1:
            break;

        case 0: /* Child: immediately exits to become zombie */
        {
            printf("In the child process\n");
            printf("My PID is %d, my parent PID is %d\n", getpid(), getppid());
            printf("Child (PID=%d) exiting\n", getpid());
            exit(EXIT_SUCCESS);
        }

        default: /* Parent */
        {
            printf("In the parent process\n");
            printf("My PID is %d, my child PID is %d\n", getpid(), child_pid);
            while (1)
                ;
        }
    }

    return 0;
}

void print_wait_status(const char *msg, const int status)
{
    if (WIFEXITED(status))
    {
        printf("Normally termination, status = %d\n", WEXITSTATUS(status));
    }
    else if (WIFSIGNALED(status))
    {
        printf("killed by signal, value = %d (%s)\n", WTERMSIG(status), strsignal(WTERMSIG(status)));
    }
    else if (WCOREDUMP(status))
    {
        printf(" (core dumped)");
        printf("\n");
    }
    else if (WIFSTOPPED(status))
    {
        printf("child stopped by signal %d (%s)\n",
               WSTOPSIG(status), strsignal(WSTOPSIG(status)));
    }
    else if (WIFCONTINUED(status))
    {
        printf("child continued\n");
    }
    else
    { /* Should never happen */
        printf("what happened to this child? (status=%x)\n",
               (unsigned int)status);
    }

    return;
}


void sig_handler(int signum)
{
    int rv, status;
    printf("Hello from sig_handler() function\n");

    /* Print the end status of the child process */
    rv = wait(&status);
    if (rv == -1)
    {
        printf("wait() unsucessful\n");
    }
    else
    {
        print_wait_status(NULL, status);
    }
}
