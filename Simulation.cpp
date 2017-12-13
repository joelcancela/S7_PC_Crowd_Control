#include "Simulation.h"

void *tick(void *arguments);

static pthread_mutex_t simulation_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond_var = PTHREAD_COND_INITIALIZER;

struct arg_struct {
    Simulation *instance;
    int thread_number;
};

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond) {
    // Update simulation properties
    this->people = people;
    this->four_threads_cond = four_threads_cond;
    this->bench_time_cond = bench_time_cond;

    // Data model
    this->dataGrid = new Datagrid();

    // Initialize obstacles
    //
    // Constraints:
    // max{x=459, y=114}
    // min{x=10, y=10}

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
            while (p->getNextDestination(instance->dataGrid) != nullptr) {
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
            Personne *p = dynamic_cast<Personne *>(personnes[0]);
            personnes.erase(personnes.begin());
            delete p;
        }

    }
}

Simulation::~Simulation() {
    // Clean obstacles
    this->obstacles.clear();

    // Clean personnes
    this->personnes.clear();
}

std::vector<Entity *> Simulation::get_vObstacles() {
    // TODO : must sum obstacle each grid
    return nullptr;
}

std::vector<Entity *> Simulation::get_vPersonnes() {
    // TODO : must sum obstacle each grid
    return nullptr;
}

bool Simulation::isRunning() {
    return (this->get_vPersonnes().size() > 0) ? true : false;
}

