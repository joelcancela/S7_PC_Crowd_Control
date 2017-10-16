#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Personne.h"

#define GRID_SIZE_X 512
#define GRID_SIZE_Y 128

class Simulation
{
	double people;
	int four_threads_cond;
	int bench_time_cond;
	bool dataGrid[GRID_SIZE_X][GRID_SIZE_Y] = {}; // Model, false cell is free, true cell is not free

	std::vector<Entity*> obstacles;
	std::vector<Entity*> personnes;
	
public:
	Simulation(double people, int four_threads_cond, int bench_time_cond);
	~Simulation();
	void fill_grid(Entity* e);
	std::vector<Entity*> get_vObstacles();
	std::vector<Entity*> get_vPersonnes();
};

