#include "Simulation.h"

Simulation::Simulation()
{
	// Initialize grid
	this->obstacles.push_back(new Obstacle( ));

	/*
	Personne* p1 = new Personne(10, 10);
	Personne* p2 = new Personne(20, 20);
	
	matrix[10][10] = p1;
	matrix[20][20] = p2;
	*/
}

Simulation::~Simulation()
{
}

std::vector<Entity*> Simulation::get_vObstacles()
{
	return this->obstacles;
}