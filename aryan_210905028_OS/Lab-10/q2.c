#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_RESOURCES 3 // Number of resource types
#define NUM_PROCESSES 5 // Number of processes

int available[NUM_RESOURCES];
int maximum[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
pthread_mutex_t mutex;

// Function to check if the system is in a safe state
int isSafeState(int process, int request[]) {
    // Temporary arrays to simulate resource allocation
    int temp_available[NUM_RESOURCES];
    int temp_allocation[NUM_PROCESSES][NUM_RESOURCES];
    int temp_need[NUM_PROCESSES][NUM_RESOURCES];

    for (int i = 0; i < NUM_RESOURCES; i++) {
        temp_available[i] = available[i] - request[i];
        temp_allocation[process][i] = allocation[process][i] + request[i];
        temp_need[process][i] = need[process][i] - request[i];
    }

    // Check if the system is in a safe state
    int work[NUM_RESOURCES];
    int finish[NUM_PROCESSES] = {0};

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = temp_available[i];
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            int j;
            for (j = 0; j < NUM_RESOURCES; j++) {
                if (temp_need[i][j] > work[j]) {
                    break;
                }
            }
            if (j == NUM_RESOURCES) {
                finish[i] = 1;
                for (int k = 0; k < NUM_RESOURCES; k++) {
                    work[k] += temp_allocation[i][k];
                }
                i = -1; // Start from the beginning
            }
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (!finish[i]) {
            return 0; // System is not in a safe state
        }
    }

    return 1; // System is in a safe state
}

// Function to request resources
void requestResources(int process, int request[]) {
    pthread_mutex_lock(&mutex);

    if (process < 0 || process >= NUM_PROCESSES) {
        printf("Invalid process index\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            printf("Process %d's request exceeds its maximum or available resources\n", process);
            pthread_mutex_unlock(&mutex);
            return;
        }
    }

    if (isSafeState(process, request)) {
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }
        printf("Process %d: Request granted\n", process);
    } else {
        printf("Process %d: Request denied (unsafe state)\n", process);
    }

    pthread_mutex_unlock(&mutex);
}

// Function to release resources
void releaseResources(int process, int release[]) {
    pthread_mutex_lock(&mutex);

    if (process < 0 || process >= NUM_PROCESSES) {
        printf("Invalid process index\n");
        pthread_mutex_unlock(&mutex);
        return;
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (release[i] > allocation[process][i]) {
            printf("Process %d is releasing more resources than allocated\n", process);
            pthread_mutex_unlock(&mutex);
            return;
        }
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }

    printf("Process %d: Resources released\n", process);

    pthread_mutex_unlock(&mutex);
}

// Thread function simulating processes
void *processThread(void *arg) {
    int process = *((int *)arg);

    // Simulate requests and releases
    int request[NUM_RESOURCES];
    int release[NUM_RESOURCES];

    // Initialize request and release arrays here

    // Simulate requests and releases multiple times
    for (int i = 0; i < 5; i++) {
        requestResources(process, request);
        releaseResources(process, release);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_PROCESSES];
    int process_ids[NUM_PROCESSES];

    // Initialize available, maximum, allocation, and need arrays here

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create and start threads
    for (int i = 0; i < NUM_PROCESSES; i++) {
        process_ids[i] = i;
        pthread_create(&threads[i], NULL, processThread, &process_ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up and exit
    pthread_mutex_destroy(&mutex);

    return 0;
}
