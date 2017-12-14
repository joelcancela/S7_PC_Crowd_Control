#include "Simulation.h"
#include "Personne.h"

void *tick(void *arguments);

void *tick_four(void *arguments);

static bool ended = false;

struct arg_struct {
    Simulation *instance;
    int thread_number;

};

Simulation::Simulation(unsigned int people, int four_threads_cond, int bench_time_cond) {
    // Update simulation properties
    this->people = people;
    this->four_threads_cond = four_threads_cond;
    this->bench_time_cond = bench_time_cond;

    if (four_threads_cond > 0) {

        // Data model as ARENA DIVIDED
        this->dA = new Datagrid(0, 0, 10, people / 4, 2);    // SEED = n°10
        this->dB = new Datagrid(128, 0, 20, people / 4, 2);    // SEED = n°20
        this->dC = new Datagrid(0, 65, 32, people / 4, 2);    // SEED = n°32
        this->dD = new Datagrid(128, 65, 48, people / 4, 2);    // SEED = n°48
    } else {

        // Data model as ARENA
        this->simpleArena = new Datagrid(0, 0, 64, people, 1);      // SEED = n°64
    }
}

// Compute the next frame
void *tick(void *arguments) {

    struct arg_struct *args = (struct arg_struct *) arguments;
    int nb = args->thread_number;
    Simulation *instance = args->instance;
    Personne *p = dynamic_cast<Personne *>(instance->get_vPersonnes()[nb]);

    //Tant que la personne n'est pas sortie
    while (!p->has_escaped()) {

        // Fetch future coordinates
        std::vector<int> dest = p->getNextDestination(); // THIS IS FAIL ?

        // Fetch associated mutex of the given coordinates
        Cell *c = p->getDatagrid()->getCellAt(dest[0], dest[1]);
        pthread_mutex_t *mutex = c->getMutex();
        pthread_cond_t *cond = c->getCond();


        while (pthread_mutex_trylock(mutex) != 0) {          //on essaie de prendre le lock pour consulter l'état de la case ou on veut aller
            std::cout << "Taking mutex" << std::endl;
            while (!c->isEmpty()) {                 //si elle est occupé
                std::cout << "sleeping" << std::endl;
                pthread_cond_wait(cond, mutex);    //on dort et on relache le mutex
            }

            //elle est pas occupé
            std::cout << "moving" << std::endl;
            p->move();                      //on bouge
            std::cout << "moved" << std::endl;
            pthread_mutex_unlock(mutex);    //on relache le mutex
            std::cout << "rel mutex" << std::endl;
            pthread_cond_broadcast(cond);   // on reveille les autres threads qui attendaient cette case
            std::cout << "bc" << std::endl;
        }
        std::cout << "out of inner while" << std::endl;
    }
    std::cout << "OUTTTTTTTTTTTT" << std::endl;
    std::cout << "!!!!!!!Thread #" << nb << " id:" << pthread_self() << " ma personne est sortie!!!!!!!" << std::endl;
    return nullptr;
}

void create_thread(pthread_t thread_persons[], int i, Simulation *pSimulation) {
    auto *args = new arg_struct();
    args->instance = pSimulation;
    args->thread_number = i;
    int error = pthread_create(&thread_persons[i], NULL, &tick, (void *) args);
    if (error) {
        std::cout << "Error when creating threads";
    }
}

void create_four_thread(pthread_t thread_persons[], int i, Simulation *pSimulation) {
    auto *args = new arg_struct();
    args->instance = pSimulation;
    args->thread_number = i;
    int error = pthread_create(&thread_persons[i], NULL, &tick_four, (void *) args);
    if (error) {
        std::cout << "Error when creating threads";
    }
}

void *tick_four(void *arguments) {//TODO 4 files d'attente boucle sur les personnes et les files en mutex
    struct arg_struct *args = (struct arg_struct *) arguments;
    int nb = args->thread_number;
    Simulation *instance = args->instance;
    Datagrid *grid = nullptr;
    if (nb == 0) {
        grid = instance->dA;
    } else if (nb == 1) {
        grid = instance->dB;
    } else if (nb == 2) {
        grid = instance->dC;
    } else if (nb == 3) {
        grid = instance->dD;
    }

    while (grid->get_vPersonnes().size() != 0) {
        for (int i = 0; i < grid->get_vPersonnes().size(); i++) {
            Personne *p = dynamic_cast<Personne *>(grid->get_vPersonnes()[i]);
            int old_x = p->get_x();
            int old_y = p->get_y();
            //p->move;
            int new_x = p->get_x();
            int new_y = p->get_y();
            if (p->has_escaped()) {
                grid->get_vPersonnes().erase(grid->get_vPersonnes().begin() + i);
                std::cout << "!!!!!!!Thread #" << nb << " ma personne est sortie!!!!!!!" << std::endl;
            }
        }
    }

    return nullptr;
}

void Simulation::start() {
    if (four_threads_cond) {
        pthread_t thread_persons[4];
        for (int i = 0; i < 4; ++i) {
            create_four_thread(thread_persons, i, this);
        }
        for (int j = 0; j < 4; j++) {
            pthread_join(thread_persons[j], NULL);
        }
    } else {
        pthread_t thread_persons[(int) people];
        for (int i = 0; i < people; ++i) {//0-255
            create_thread(thread_persons, i, this);
        }
        for (int j = 0; j < people; j++) {
            pthread_join(thread_persons[j], NULL);
        }
    }

    ended = true;
}

std::vector<Entity *> Simulation::get_vPersonnes() {
    if (four_threads_cond > 0) {
        std::vector<Entity *> vPersonnes;

        // Merge four arrays
        vPersonnes.reserve(
                this->dA->get_vPersonnes().size() +
                this->dB->get_vPersonnes().size() +
                this->dC->get_vPersonnes().size() +
                this->dD->get_vPersonnes().size()
        ); // preallocate memory
        vPersonnes.insert(vPersonnes.end(), this->dA->get_vPersonnes().begin(), this->dA->get_vPersonnes().end());
        vPersonnes.insert(vPersonnes.end(), this->dB->get_vPersonnes().begin(), this->dB->get_vPersonnes().end());
        vPersonnes.insert(vPersonnes.end(), this->dC->get_vPersonnes().begin(), this->dC->get_vPersonnes().end());
        vPersonnes.insert(vPersonnes.end(), this->dD->get_vPersonnes().begin(), this->dD->get_vPersonnes().end());

        return vPersonnes;
    }
    return this->simpleArena->get_vPersonnes();
}

bool Simulation::isRunning() {
    return !ended;
}

