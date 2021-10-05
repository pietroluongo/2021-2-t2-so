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
        flamenguistaQuerEntrar(*id);
        printf ("Eu sou flamenguista %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        flamenguistaSai(*id);
        printf ("Eu sou flamenguista %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
    pthread_exit(0);
}

void* thread_vascaino(void* param) {
    int* id = (int*) param;
    while (1) {
        printf ("Eu sou o(a) vascaino %d:...Estou apertado(a)! Vou no banheiro!\n",*id);
        vascainoQuerEntrar(*id);
        printf ("Eu sou vascaino %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        vascainoSai(*id);
        printf ("Eu sou vascaino %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
    pthread_exit(0);
}

void torcedores_instantiate() {
    pthread_t* threads = malloc(2 * THREAD_COUNT_BY_TEAM * sizeof(pthread_t));
    for(int i = 0; i < 2 * THREAD_COUNT_BY_TEAM; i++) {
        if(i % 2 == 0) {
            if (pthread_create(&threads[i], NULL, &thread_flamenguista, (void*) &i) != 0) {
                printf("failed to create thread %d\n", i);
                exit(1);
            }
        }
        else {
            if (pthread_create(&threads[i], NULL, &thread_vascaino, (void*) &i) != 0) {
            printf("failed to create thread %d\n", i);
            exit(1);
            }
        }
    }
    for(int i = 0; i < 2 * THREAD_COUNT_BY_TEAM; i++) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
}