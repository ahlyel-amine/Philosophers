#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
struct alo{
    sem_t *semaphore;
    int   amine;
};
#define BUFFER_SIZE 1024
#define SHARED_MEMORY_SIZE 1024
#define SEMAPHORE_NAME "/my_semaphore"

void alo(void *amine)
{
    for (int i = 0; i < 15; i++) {
        printf("thread try to lock\n");
        sem_wait(((struct alo *)amine)->semaphore);
        printf("thread lock\n");
        printf("thread\t\t\t: %d\n", ((struct alo *)amine)->amine);
        printf("thread unlock\n");
        sem_post(((struct alo *)amine)->semaphore);
    }
}

int main() {
    struct alo  *so;
    pthread_t   thread;
    pid_t       pid;
    so = malloc(sizeof(struct alo));
    sem_unlink(SEMAPHORE_NAME);
    so->semaphore = sem_open(SEMAPHORE_NAME, O_CREAT, 0644, 2);
    so->amine = 0;
    if (so->semaphore == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }
    pid = fork();
    if (pid == -1){
        perror("sem_open");
        sem_unlink(SEMAPHORE_NAME);
        exit(1);
    }
    if (!pid)
    {
        for (int i = 0; i < 15; i++)
        {
            printf("child proccess try to lock\n");
            sem_wait(so->semaphore);
            printf("child proccess lock\n");
            printf("child proccess before\t: %d\n", so->amine);
            so->amine += 1;
            printf("child proccess after\t: %d\n", so->amine);
            printf("child proccess unlock\n");
            sem_post(so->semaphore);
            // usleep(100);
        }
        sem_unlink(SEMAPHORE_NAME);
        exit(0);
    }
    if (pid)
    {
        usleep(100);
        pthread_create(&thread, NULL, (void *)alo, so);
        pthread_join(thread, NULL);
        waitpid(pid, NULL, 0);

    sem_unlink(SEMAPHORE_NAME);
    }
    return 0;
}
