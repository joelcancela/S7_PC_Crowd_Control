#include "Simulation.h"

Simulation::Simulation(unsigned int p)
{
	// Initialize obstacles
	// max{x=459, y=114}
	// min{x=10, y=10}
	this->obstacles.push_back(new Obstacle(10, 10));
	this->obstacles.push_back(new Obstacle(76, 75));
	this->obstacles.push_back(new Obstacle(230, 64));
	this->obstacles.push_back(new Obstacle(459, 50));
	this->obstacles.push_back(new Obstacle(150, 114));

	// Initialize personnes
	int max_p = (int)pow(2, p);
	for (int i = 0; i < max_p; i++) {
		int x = rand() % (GRID_SIZE_X / OBSTACLE_SIZE_REDUCTION_FACTOR) + 1;
		int y = rand() % (GRID_SIZE_X / OBSTACLE_SIZE_REDUCTION_FACTOR) + 1;
		this->personnes.push_back(new Personne(x, y));
		break;
	}
}

Simulation::~Simulation()
{
	// Clean obstacles
	for (unsigned int i = 0; i < this->obstacles.size(); i++) {
		delete this->obstacles[i];
	}
}

std::vector<Entity*> Simulation::get_vObstacles() {
	return this->obstacles;
}

std::vector<Entity*> Simulation::get_vPersonnes() {
	return this->personnes;
}