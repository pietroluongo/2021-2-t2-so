#include "petshop.h"

Petshop* ps_init(int maxPetsInRoom) {
    Petshop* ps = (Petshop*) malloc(sizeof(Petshop));

    ps->maxPetsInRoom = maxPetsInRoom;
    ps->dogsWaiting = 0;
    ps->catsWaiting = 0;
    ps->dogsBeingTreated = 0;
    ps->catsBeingTreated = 0;
    pthread_mutex_init(&ps->dogMutex, NULL);
    pthread_mutex_init(&ps->catMutex, NULL);
    sem_init(&ps->roomAvailable, 0, maxPetsInRoom);

    return ps;
}

void ps_mainLoop(Petshop* ps, int nDogs, int nCats) {
    pthread_t dogThreads[nDogs];
    pthread_t catThreads[nCats];
    
    for (int i = 0; i < nDogs; i++){
        petshopid* psid = (petshopid*) malloc(sizeof(petshopid));
        psid->ps = ps;
        psid->id = i;
        pthread_create(&dogThreads[i], NULL, ps_um_cao_quer_servico, (void*)psid);
    }
    
    for (int i = 0; i < nCats; i++){
        petshopid* psid = (petshopid*) malloc(sizeof(petshopid));
        psid->ps = ps;
        psid->id = i;
        pthread_create(&catThreads[i], NULL, ps_um_gato_quer_servico, (void*)psid);
    }
    
    for (int i = 0; i < nDogs; i++) {
        pthread_join(dogThreads[i], NULL);
    }

    for (int i = 0; i < nCats; i++) {
        pthread_join(catThreads[i], NULL);
    }
}

void* ps_um_cao_quer_servico(void* psid) {
    petshopid* petshopandid = (petshopid*)psid;
    Petshop* ps = petshopandid->ps;
    int sleepTime = (1 + rand() % 5) * 3;
    sleep(sleepTime);
    printf("iteration %d: dog %d has arrived!\n", sleepTime / 3, petshopandid->id);
    
    pthread_mutex_lock(&ps->dogMutex);
    ps->dogsWaiting++;
    pthread_mutex_unlock(&ps->dogMutex);

    while (ps->catsBeingTreated > 0) {}

    pthread_mutex_lock(&ps->dogMutex);
    sem_wait(&ps->roomAvailable);
    ps->dogsWaiting--;
    ps->dogsBeingTreated++;
    pthread_mutex_unlock(&ps->dogMutex);

    sleep(1);
    ps_cao_atendido(ps, petshopandid->id);
}

void ps_cao_atendido(Petshop* ps, int id) {
    sem_post(&ps->roomAvailable);
    pthread_mutex_lock(&ps->dogMutex);
    ps->dogsBeingTreated--;
    pthread_mutex_unlock(&ps->dogMutex);
    printf("dog %d finished being treated\n", id);
}

void* ps_um_gato_quer_servico(void* psid) {
    petshopid* petshopandid = (petshopid*)psid;
    Petshop* ps = petshopandid->ps;
    int sleepTime = (1 + rand() % 5) * 3;
    sleep(sleepTime);
    printf("iteration %d: cat %d has arrived!\n", sleepTime / 3, petshopandid->id);

    pthread_mutex_lock(&ps->catMutex);
    ps->catsWaiting++;
    pthread_mutex_unlock(&ps->catMutex);
    int semValue = 0;

    while (ps->dogsBeingTreated > 0 || ps->dogsWaiting > 0) {}

    pthread_mutex_lock(&ps->catMutex);
    sem_wait(&ps->roomAvailable);
    ps->catsWaiting--;
    ps->catsBeingTreated++;
    pthread_mutex_unlock(&ps->catMutex);

    sleep(1);
    ps_gato_atendido(ps, petshopandid->id);
}

void ps_gato_atendido(Petshop* ps, int id) {
    sem_post(&ps->roomAvailable);
    pthread_mutex_lock(&ps->catMutex);
    ps->catsBeingTreated--;
    pthread_mutex_unlock(&ps->catMutex);
    printf("cat %d finished being treated\n", id);
}

void ps_free(Petshop* ps) {
    pthread_mutex_destroy(&ps->dogMutex);
    pthread_mutex_destroy(&ps->catMutex);
    sem_destroy(&ps->roomAvailable);

    free(ps);
}