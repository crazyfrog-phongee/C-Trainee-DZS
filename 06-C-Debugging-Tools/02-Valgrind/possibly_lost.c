#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

static void *handle_th1(void *args)
{
    printf("Hello from ThreadID1 with %ld\n", pthread_self());
    pthread_exit(NULL);
}

static void *handle_th2(void *args)
{
    printf("Hello from ThreadID2 with %ld\n", pthread_self());
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    int ret;
    pthread_t thread_id1, thread_id2;

    ret = pthread_create(&thread_id1, NULL, &handle_th1, NULL);
    if (ret != 0)
    {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    ret = pthread_create(&thread_id2, NULL, &handle_th2, NULL);
    if (ret != 0)
    {
        printf("pthread_create() error number = %d\n", ret);
        return -1;
    }

    pthread_join(thread_id1, NULL);
    /* pthread_join(thread_id2, NULL); */

    return 0;
}
