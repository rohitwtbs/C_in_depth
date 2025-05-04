
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 3
#define COUNT_TO 5

// Mutex for thread synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Structure to pass data to threads
typedef struct {
    int thread_id;
} thread_data;

// Thread function
void* count_numbers(void* arg) {
    thread_data* data = (thread_data*)arg;
    
    for (int i = 1; i <= COUNT_TO; i++) {
        // Lock mutex before printing
        pthread_mutex_lock(&mutex);
        
        printf("Thread %d counting: %d\n", data->thread_id, i);
        
        // Unlock mutex after printing
        pthread_mutex_unlock(&mutex);
        
        // Sleep for a short time to simulate work
        usleep(100000);  // 0.1 seconds
    }
    
    printf("Thread %d finished counting\n", data->thread_id);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data thread_data_array[NUM_THREADS];
    
    printf("Creating %d threads...\n", NUM_THREADS);
    
    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].thread_id = i + 1;
        if (pthread_create(&threads[i], NULL, count_numbers, &thread_data_array[i]) != 0) {
            printf("Failed to create thread %d\n", i + 1);
            return 1;
        }
    }
    
    // Wait for all threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Destroy mutex
    pthread_mutex_destroy(&mutex);
    
    printf("All threads completed!\n");
    return 0;
}
