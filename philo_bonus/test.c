#include <unistd.h>
#include <stdio.h>
#include <sys/semaphore.h>
#include <sys/wait.h>
sem_t mtx;

int      routine(int *i)
{
    // protect the critical section of you code
    // Our critical section is : *i++
    int k = 0;
    while (k++ < 100000)
    {
        sem_wait(&mtx); 
        printf("%d lock %d th time\n", *i, k);
        sleep(1);
        sem_post(&mtx);
        printf("%d unlock\n", *i);
    }
    return (100);
}

int main()
{
    int i = 0;
    printf("\e[1;94m amine \e[0m\n");

    sem_init(&mtx, 0, 1);
    int a = fork();
    if (a == -1)
        return (sem_destroy(&mtx), 1);
    i = 1;
    if (!a)
        routine(&i);
    i = 2;
    // int b = fork();
    // if (b == -1)
    //     return (sem_destroy(&mtx), 1);
    // if (!b)
        routine(&i);
    // waitpid(a, NULL, 0);
    // waitpid(b, NULL, 0);
    // //  create t1
    // pthread_create(&t1, NULL, (void *)foo, &i);
    // //  create t2
    // pthread_create(&t2, NULL, (void *)foo, &i);
    // pthread_create(&t3, NULL, (void *)foo, &i);
    // /* Waiting for threads t1, t2, main thread*/
    // pthread_join(t1, NULL);
    // pthread_join(t2, NULL);
    // pthread_join(t3, NULL);
    // printf("%d\n", i);    
    return (0);
}
