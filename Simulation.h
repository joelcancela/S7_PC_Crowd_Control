#ifndef SIMULATION_H
#define SIMULATION_H

#include <mutex>
#include <cstring>
#include <chrono>
#include <thread>
#include "shared_header.h"
#include "Entity.h"
#include "Datagrid.h"
#include "Personne.h"
#include "Obstacle.h"
#include "Command.h"

class Simulation
{
	int four_threads_cond;
	int bench_time_cond;

	// PART I

	Datagrid* arena;

	// PART II PROJECT

	// A | B
	// __|__
	// C | D
	//   |

	// ARENA MODEL
	Datagrid* dA;
	Datagrid* dB;
	Datagrid* dC;
	Datagrid* dD;

public:
	Simulation(double people, int four_threads_cond, int bench_time_cond);
	~Simulation();
	std::vector<Entity*> get_vObstacles();
	std::vector<Entity*> get_vPersonnes();
	void start();
	bool isRunning();
};

#endif