#include "MonitorBanheiro.h"
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

enum QuemEstaNoBanheiro {
    Flamengo,
    Vasco
};

void flamenguistaQuerEntrar(int id) {
    pthread_mutex_lock(&mutex);
}

void flamenguistaSai(int id) {
    pthread_mutex_unlock(&mutex);
}

void vascainoQuerEntrar(int id) {
    pthread_mutex_lock(&mutex);
}

void vascainoSai(int id) {
    pthread_mutex_unlock(&mutex);
}