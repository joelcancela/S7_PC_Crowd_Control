#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Datagrid.h"
#include "Personne.h"
#include "Obstacle.h"
#include "Command.h"

class Simulation
{
	double people;
	int four_threads_cond;
	int bench_time_cond;

	Datagrid* dataGrid;

	std::vector<Entity*> obstacles;
	std::vector<Entity*> personnes;
	
public:
	Simulation(double people, int four_threads_cond, int bench_time_cond);
	~Simulation();
	void fill_grid(Entity* e);
	std::vector<Entity*> get_vObstacles();
	std::vector<Entity*> get_vPersonnes();
	bool isRunning();
	void tick();

private:
	static std::vector<int> azimuth(int, int);				// Helper for creating a path
	std::queue<Command*> path(int, int, std::vector<int>);	// Compute path to the azimuth

	// More helpers for path finding
	std::vector<int> getNextPos(CommandN*, int, int);
	std::vector<int> getNextPos(CommandNW*, int, int);
	std::vector<int> getNextPos(CommandW*, int, int);
};
