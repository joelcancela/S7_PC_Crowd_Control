#include "Simulation.h"
#include "Personne.h"

void *tick(void *arguments);

static pthread_mutex_t simulation_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

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
        this->dA = new Datagrid(0, 0, 10,       people / 4, 2);    // SEED = n°10
        this->dB = new Datagrid(128, 0, 20,     people / 4, 2);    // SEED = n°20
        this->dC = new Datagrid(0, 65, 32,      people / 4, 2);    // SEED = n°32
        this->dD = new Datagrid(128, 65, 48,    people / 4, 2);    // SEED = n°48
    }
    else {

        // Data model as ARENA
        this->simpleArena = new Datagrid(0, 0, 64, people, 1);      // SEED = n°64
    }
}

// Compute the next frame
void *tick(void *arguments) {
    //pthread_mutex_lock(&simulation_mutex);
    struct arg_struct *args = (struct arg_struct *) arguments;
    int nb = args->thread_number;
    Simulation *instance = args->instance;
    Personne *p = dynamic_cast<Personne *>(instance->get_vPersonnes()[nb]);
    while (!p->has_escaped()) {
        int old_x = p->get_x();
        int old_y = p->get_y();
        p->move();
        int new_x = p->get_x();
        int new_y = p->get_y();
        if ((old_x == new_x) && (old_y == new_y)) {//We just blocked
            std::cout << "Blocked @" << new_x << ", " << new_y << std::endl;
            //pthread_cond_broadcast(&cond_var);
            while (p->getNextDestination()[2] == -1) {
                usleep(1);
                //pthread_cond_wait(&cond_var, &simulation_mutex);
            }
            std::cout << "Thread #" << nb << " id:" << pthread_self() << " se reveille" << std::endl;;
        } else {
            std::cout << "Thread #" << nb << " id:" << pthread_self() << " a deplace " << p->to_string() << std::endl;
        }
    }
    std::cout << "!!!!!!!Thread #" << nb << " id:" << pthread_self() << " ma personne est sortie!!!!!!!" << std::endl;
    //pthread_cond_broadcast(&cond_var);
    //pthread_mutex_unlock(&simulation_mutex);
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

void Simulation::start() {
    if (four_threads_cond) {
        //TODO split
    } else {
        pthread_t thread_persons[(int) people];
        for (int i = 0; i < people; ++i) {
            create_thread(thread_persons, i, this);
        }
        for (int j = 0; j < people; j++) {
            pthread_join(thread_persons[j], NULL);
        }
        while (!get_vPersonnes().empty()) {
            Personne *p = dynamic_cast<Personne *>(simpleArena->get_vPersonnes()[0]);
            simpleArena->get_vPersonnes().erase(simpleArena->get_vPersonnes().begin());
            delete p;
        }

    }
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
        vPersonnes.insert( vPersonnes.end(), this->dA->get_vPersonnes().begin(), this->dA->get_vPersonnes().end() );
        vPersonnes.insert( vPersonnes.end(), this->dB->get_vPersonnes().begin(), this->dB->get_vPersonnes().end() );
        vPersonnes.insert( vPersonnes.end(), this->dC->get_vPersonnes().begin(), this->dC->get_vPersonnes().end() );
        vPersonnes.insert( vPersonnes.end(), this->dD->get_vPersonnes().begin(), this->dD->get_vPersonnes().end() );

        return vPersonnes;
    }
    return this->simpleArena->get_vPersonnes();
}

bool Simulation::isRunning() {
    return this->get_vPersonnes().size() > 0;
}

