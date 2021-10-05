#include "MonitorBanheiro.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

enum QuemEstaNoBanheiro {
    Flamengo,
    Vasco
};

void flamenguistaQuerEntrar(int id) {
    printf("flamenguisto %d esperando\n", id);
    pthread_mutex_lock(&mutex);
}

void flamenguistaSai(int id) {
    printf("flamenguisto %d saindo\n", id);
    pthread_mutex_unlock(&mutex);
}

void vascainoQuerEntrar(int id) {
    printf("vascaine %d esperando\n", id);
    pthread_mutex_lock(&mutex);
}

void vascainoSai(int id) {
    printf("vascaine %d saindo\n", id);
    pthread_mutex_unlock(&mutex);
}