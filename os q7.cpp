#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    int shmid;
    key_t key;
    char *shm, *s;

    // Generate a unique key for shared memory
    key = ftok(".", 'S');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    // Create a shared memory segment
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to the process's address space
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    // Fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {  // Child process
        printf("Child process writing to shared memory...\n");
        s = shm;
        *s = 'H';  // Write to shared memory
        s++;       // Move to the next character
        *s = 'i';  // Write to shared memory
        s++;       // Move to the next character
        *s = '\0'; // Null-terminate the string
        exit(0);
    } else {  // Parent process
        wait(NULL); // Wait for child to finish
        printf("Parent process reading from shared memory: %s\n", shm);
    }

    // Detach the shared memory segment from the process's address space
    if (shmdt(shm) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Delete the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }

    return 0;
}
