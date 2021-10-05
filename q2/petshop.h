#ifndef PETSHOP_H_
#define PETSHOP_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

// none = 0
// dog = 1
// cat = 2
typedef struct petshop {
    unsigned int maxPetsInRoom;
    unsigned int dogsWaiting;
    unsigned int catsWaiting;
    unsigned int dogsBeingTreated;
    unsigned int catsBeingTreated;
    pthread_mutex_t dogMutex;
    pthread_mutex_t catMutex;
    sem_t roomAvailable;
} Petshop;

typedef struct petshopAndId {
    Petshop* ps;
    int id;
} petshopid;

Petshop* ps_init(int maxPetsInRoom);

void ps_mainLoop(Petshop* ps, int nDogs, int nCats);

void* ps_um_cao_quer_servico(void* psid);
void ps_cao_atendido(Petshop* ps, int id);

void* ps_um_gato_quer_servico(void* psid);
void ps_gato_atendido(Petshop* ps, int id);

void ps_free(Petshop* ps);

#endif
