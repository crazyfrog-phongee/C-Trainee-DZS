#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{   
    /* Before run execl() */
    printf("Before running execl()\n");
    printf("Process ID: %d\n", getpid());
    printf("Parent Process ID: %d\n", getppid());

    printf("Run command <ls -lah> after 2 seconds\n");
    sleep(2);
    execl("./bin/hello_dzs", "Nguyen", "Trong", "Phong", "17082001", "DZS", NULL);

    printf("If we get here, something went wrong :<\n");
    return 0;   
}