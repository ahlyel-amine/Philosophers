#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

pthread_mutex_t mtx;

int      foo(int *i)
{
    // protect the critical section of you code
    // Our critical section is : *i++
    pthread_mutex_init(&mtx, NULL); 
    int k = 0;
    while (k++ < 100000)
    {
        // pthread_mutex_try_lock()
        // mtx will be accessed by : t1 , t2
        pthread_mutex_lock(&mtx);
        printf("lock\n");
        (*i)++;
        pthread_mutex_unlock(&mtx);
        printf("unlock\n");
    }
    pthread_mutex_destroy(&mtx);
    return (100);
}

int main()
{
    pthread_t   t1;
    pthread_t   t2;
    pthread_t   t3;
    int i = 0;
    pthread_create(&t1, NULL, (void *)foo, &i);
    pthread_create(&t2, NULL, (void *)foo, &i);
    pthread_create(&t3, NULL, (void *)foo, &i);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    printf("%d\n", i);    
    return (0);
}
