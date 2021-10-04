#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include "Torcedores.h"
#include "MonitorBanheiro.h"

#define BATHROOM_SIZE        3
#define THREAD_COUNT_BY_TEAM 10


void* thread_flamenguista(void* param) {
    int* id = (int*) param;
    while (1) {
        printf ("Eu sou o(a) flamenguista %d:...Estou apertado(a)! Vou no banheiro!\n",*id);
        flamenguistaQuerEntrar();
        printf ("Eu sou flamenguista %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        flamenguistaSai();
        printf ("Eu sou flamenguista %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
    pthread_exit(0);
}

void* thread_vascaino(void* param) {
    int* id = (int*) param;
    while (1) {
        printf ("Eu sou o(a) vascaino %d:...Estou apertado(a)! Vou no banheiro!\n",*id);
        vascainoQuerEntrar();
        printf ("Eu sou vascaino %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        vascainoSai();
        printf ("Eu sou vascaino %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
    pthread_exit(0);
}

void torcedores_instantiate() {
    pthread_t* threads = malloc(2 * THREAD_COUNT_BY_TEAM * sizeof(pthread_t));
    printf("all ok %d\n", 2 * THREAD_COUNT_BY_TEAM);
    for(int i = 0; i < THREAD_COUNT_BY_TEAM; i++) {
        printf("creating flamengo\n");
        pthread_create(&threads[i], NULL, thread_flamenguista, NULL);
        printf("created flamengo\n");
    }
    for(int i = THREAD_COUNT_BY_TEAM; i < 2*THREAD_COUNT_BY_TEAM; i++) {
        pthread_create(&threads[i], NULL, thread_vascaino, NULL);
    }
    free(threads);
}