#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"

#define GRID_SIZE_X 512
#define GRID_SIZE_Y 128

class Simulation
{
	std::vector<Entity*> obstacles;
	
public:
	Simulation();
	~Simulation();
	std::vector<Entity*> get_vObstacles();
};

