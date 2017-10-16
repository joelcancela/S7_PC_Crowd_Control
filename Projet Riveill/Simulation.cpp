#include "Simulation.h"

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond) {
    this->people = people;
    this->four_threads_cond = four_threads_cond;
    this->bench_time_cond = bench_time_cond;
    // Initialize obstacles
    this->obstacles.push_back(new Obstacle(20, 20));
    this->obstacles.push_back(new Obstacle(76, 75));
    this->obstacles.push_back(new Obstacle(230, 64));
    this->obstacles.push_back(new Obstacle(450, 50));
    this->obstacles.push_back(new Obstacle(150, 90));
}

Simulation::~Simulation() {
    // Clean obstacles
    for (unsigned int i = 0; i < this->obstacles.size(); i++) {
        delete this->obstacles[i];
    }
}

std::vector<Entity *> Simulation::get_vObstacles() {
    return this->obstacles;
}