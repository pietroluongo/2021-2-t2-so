#include "MonitorBanheiro.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void flamenguistaQuerEntrar(int id) {
    pthread_mutex_lock(&mutex);
    printf("flamenguisto %d esperando\n", id);
    pthread_mutex_unlock(&mutex);
}

void flamenguistaSai(int id) {
pthread_mutex_lock(&mutex);
    printf("flamenguisto %d saindo\n", id);
    pthread_mutex_unlock(&mutex);
}

void vascainoQuerEntrar(int id) {
pthread_mutex_lock(&mutex);
    printf("vascaine %d esperando\n", id);
    pthread_mutex_unlock(&mutex);
}

void vascainoSai(int id) {
    pthread_mutex_lock(&mutex);
    printf("vascaine %d saindo\n", id);
    pthread_mutex_unlock(&mutex);
}