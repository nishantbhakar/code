
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int data = 0, readCount = 0;
pthread_mutex_t mutex;
sem_t wrt;

void* reader(void* arg) {
    int id = *(int*)arg;

    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Mutex lock failed");
        pthread_exit(NULL);
    }

    readCount++;
    if (readCount == 1) {
        if (sem_wait(&wrt) != 0) {
            perror("Semaphore wait failed");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Mutex unlock failed");
        pthread_exit(NULL);
    }

    std::cout << "Reader " << id << " reads data = " << data << std::endl;
    sleep(1);

    if (pthread_mutex_lock(&mutex) != 0) {
        perror("Mutex lock failed");
        pthread_exit(NULL);
    }

    readCount--;
    if (readCount == 0) {
        if (sem_post(&wrt) != 0) {
            perror("Semaphore post failed");
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

    if (pthread_mutex_unlock(&mutex) != 0) {
        perror("Mutex unlock failed");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

void* writer(void* arg) {
    int id = *(int*)arg;

    if (sem_wait(&wrt) != 0) {
        perror("Semaphore wait failed");
        pthread_exit(NULL);
    }

    data++;
    std::cout << "Writer " << id << " writes data = " << data << std::endl;
    sleep(1);

    if (sem_post(&wrt) != 0) {
        perror("Semaphore post failed");
        pthread_exit(NULL);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[5], writers[2];
    int reader_ids[5], writer_ids[2];

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        perror("Mutex init failed");
        return 1;
    }

    if (sem_init(&wrt, 0, 1) != 0) {
        perror("Semaphore init failed");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        if (pthread_create(&readers[i], NULL, reader, &reader_ids[i]) != 0) {
            perror("Reader thread creation failed");
        }
    }

    for (int i = 0; i < 2; i++) {
        writer_ids[i] = i + 1;
        if (pthread_create(&writers[i], NULL, writer, &writer_ids[i]) != 0) {
            perror("Writer thread creation failed");
        }
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
}