#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"

#define GRID_SIZE_X 512
#define GRID_SIZE_Y 128

class Simulation
{
	double people;
	int four_threads_cond;
	int bench_time_cond;
	std::vector<Entity*> obstacles;
	
public:
	Simulation(double people, int four_threads_cond, int bench_time_cond);
	~Simulation();
	std::vector<Entity*> get_vObstacles();
};

