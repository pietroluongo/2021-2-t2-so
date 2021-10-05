#include <time.h>
#include "petshop.h"

int main () {
    int maxPetsInRoom;
    int nDogs;
    int nCats;
    srand(time(NULL));

    printf("Please enter the max number of animals inside the room: ");
    fflush(stdout);
    scanf("%d", &maxPetsInRoom);

    printf("Now, please enter the number of dogs: ");
    fflush(stdout);
    scanf("%d", &nDogs);

    printf("Finally, please enter the number of cats: ");
    fflush(stdout);
    scanf("%d", &nCats);
    
    Petshop* ps = ps_init(maxPetsInRoom);
    
    ps_mainLoop(ps, nDogs, nCats);

    ps_free(ps);

    return 0;
}