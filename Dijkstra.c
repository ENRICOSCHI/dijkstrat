#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

// Variabili globali
int count = 0;
sem_t mutex;

// Funzione eseguita dai thread
void* thread_func(void* id) {
    int thread_id = *(int*)id;
    
    sem_wait(&mutex); // Inizio della sezione critica
    
    printf("Thread %d: count = %d\n", thread_id, ++count);
    
    sem_post(&mutex); // Fine della sezione critica
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    int i;

    // Inizializzazione del semaforo
    sem_init(&mutex, 0, 1);

    // Creazione dei thread
    for (i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    // Join dei thread
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Distruzione del semaforo
    sem_destroy(&mutex);

    return 0;
}
