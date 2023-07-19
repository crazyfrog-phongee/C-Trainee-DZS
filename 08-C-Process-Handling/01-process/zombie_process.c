#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <libgen.h>

#define CMD_SIZE 200

int main(int argc, char *argv[])
{
    char cmd[CMD_SIZE];
    pid_t child_pid;

    printf("Parent PID = %d\n", getpid());

    switch (child_pid = fork())
    {
        case -1:
            /* Handle error */
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
            sleep(3); /* Give child a chance to start and exit */

            snprintf(cmd, CMD_SIZE, "ps | grep %s", basename(argv[0]));
            cmd[CMD_SIZE - 1] = '\0'; /* Ensure string is null-terminated */
            system(cmd);              /* View zombie child */

            /* Now send the "sure kill" signal to the zombie */
            if (kill(child_pid, SIGKILL) == -1)
            {
                printf("Error kill\n");
            }

            sleep(3); /* Give child a chance to react to signal */
            printf("After sending SIGKILL to zombie (PID=%d):\n", child_pid);
            system(cmd); /* View zombie child again */

            while (1);

            exit(EXIT_SUCCESS);
        }
    }
}