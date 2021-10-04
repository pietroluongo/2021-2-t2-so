#include <stdio.h>
#include <unistd.h>
#include "Torcedores.h"
#include "MonitorBanheiro.h"

void thread_flamenguista(int* id) {
    while (1) {
        printf ("Eu sou o(a) flamenguista %d:...Estou apertado(a)! Vou no banheiro!\n",*id);
        flamenguistaQuerEntrar();
        printf ("Eu sou flamenguista %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        flamenguistaSai();
        printf ("Eu sou flamenguista %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
}

void thread_vascaino(int* id) {
    while (1) {
        printf ("Eu sou o(a) vascaino %d:...Estou apertado(a)! Vou no banheiro!\n",*id);
        vascainoQuerEntrar();
        printf ("Eu sou vascaino %d: ... UFA! Entrei no banheiro!\n",*id);
        sleep(5);
        vascainoSai();
        printf ("Eu sou vascaino %d: ... Estou aliviado! Vou torcer!\n",*id); sleep(5);
    }
}