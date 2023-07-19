#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

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

int main(int argc, char const *argv[]) /* Cấp phát stack frame cho hàm main() */
{
    pid_t child_pid;

    switch (child_pid = fork())
    {
    case -1:
        /* Handle error */
        break;

    case 0:
        /* Perform actions specific to child */
        {
            printf("My PID is: %d, my parent PID is: %d\n", getpid(), getppid());

            /* Excution of program hello_dzs */
            printf("Run command <ls -lah> after 2 seconds\n");
            sleep(2);
            execl("./bin/hello_dzs", "Nguyen", "Trong", "Phong", "17082001", "DZS", NULL);

            printf("If we get here, something went wrong :<\n");

            exit(EXIT_SUCCESS);
        }

    default:
        /* Perform actions specific to parent */
        {
            printf("\nIm the parent process, PID child process: %d\n", child_pid);

            int status, ret;
            ret = wait(&status);

            if (-1 == ret)
            {
                printf("wait() unsuccessful\n");
            }

            print_wait_status(NULL, status);

            break;
        }
    }

    return 0;
}
