#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function executed by each thread
void *thread_function(void *arg) {
    int thread_id = *((int *)arg);
    printf("Thread %d is running\n", thread_id);
    sleep(1); // Simulate some work
    printf("Thread %d is done\n", thread_id);
    return NULL;
}

int main() {
    pthread_t thread_id[2];
    int i, id[2];

    // Create two threads
    for (i = 0; i < 2; i++) {
        id[i] = i + 1;
        if (pthread_create(&thread_id[i], NULL, thread_function, &id[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for both threads to finish
    for (i = 0; i < 2; i++) {
        if (pthread_join(thread_id[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    printf("Both threads have completed\n");

    return 0;
}
