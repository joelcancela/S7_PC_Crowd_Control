#include <pthread.h>
#include <cstring>
#include <chrono>
#include <thread>
#include <zconf.h>
#include "Simulation.h"
void *tick(void *arguments);
static pthread_mutex_t simulation_mutex = PTHREAD_MUTEX_INITIALIZER;

struct arg_struct {
    Simulation *instance;
    int thread_number;
};

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond) {
    // Update simulation properties
    this->people = people;
    this->four_threads_cond = four_threads_cond;
    this->bench_time_cond = bench_time_cond;

    this->dataGrid = new Datagrid();

    // Initialize obstacles
    // max{x=459, y=114}
    // min{x=10, y=10}
    Obstacle *o = new Obstacle(10, 10);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(76, 75);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(230, 64);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(459, 50);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(150, 114);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    // Initialize personnes
    int x, y;
    for (int i = 0; i < people; i++) {
        Personne *p;
        // while we have not found a proper cell for our personne
        while (1) {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;

            if (this->dataGrid->getEntityAt(x, y) == nullptr) {
                p = new Personne(x, y);
                this->personnes.push_back(p);
                this->fill_grid(p);
                break;
            }
        }
    }


}

void Simulation::fill_grid(Entity *e) {
    std::vector<unsigned int> pos(2);
    pos[0] = e->get_x();
    pos[1] = e->get_y();

    std::vector<unsigned int> size(2);
    size[0] = e->get_size_x();
    size[1] = e->get_size_y();

    for (unsigned int x = 0; x < size[0]; ++x) {
        for (unsigned int y = 0; y < size[1]; ++y) {
            this->dataGrid->setEntityAt(pos[0] + x, pos[1] + y, e);
        }
    }
}

// Compute the next frame
void *tick(void *arguments) {
    pthread_mutex_lock(&simulation_mutex);
    struct arg_struct *args = (struct arg_struct *) arguments;
    int nb = args->thread_number;
    Simulation *instance = args->instance;
    Personne *p = dynamic_cast<Personne *>(instance->get_vPersonnes()[nb]);
    pthread_mutex_unlock(&simulation_mutex);
    while (!p->has_escaped()) {
        pthread_mutex_lock(&simulation_mutex);
        p->move();
        std::cout << "Thread #" << nb << " id:" << pthread_self() << " a déplacé " << p->to_string() << std::endl;
        pthread_mutex_unlock(&simulation_mutex);
        sleep(1);
    }
    instance->get_vPersonnes().erase(instance->get_vPersonnes().begin() + nb);
    delete p;
    return NULL;
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

    }
}

Simulation::~Simulation() {
    // Clean obstacles
    this->obstacles.clear();

    // Clean personnes
    this->personnes.clear();
}

std::vector<Entity *> Simulation::get_vObstacles() {
    return this->obstacles;
}

std::vector<Entity *> Simulation::get_vPersonnes() {
    return this->personnes;
}

bool Simulation::isRunning() {
    return (this->get_vPersonnes().size() > 0) ? true : false;
}

