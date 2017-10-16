#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Personne.h"

#define GRID_SIZE_X 512
#define GRID_SIZE_Y 128

/*
using grid = std::array<std::array<int, sizeX> sizeY>;
grid * ary = new grid;
*/

class Simulation
{
	std::vector<Entity*> obstacles;
	std::vector<Entity*> personnes;
	
public:
	Simulation(unsigned int p);
	~Simulation();
	std::vector<Entity*> get_vObstacles();
	std::vector<Entity*> get_vPersonnes();
};

