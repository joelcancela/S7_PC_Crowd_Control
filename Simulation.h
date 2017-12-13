#ifndef SIMULATION_H
#define SIMULATION_H

#include <mutex>
#include <cstring>
#include <chrono>
#include <thread>

#include "shared_header.h"
#include "Datagrid.h"

class Simulation
{
	int four_threads_cond;
	int bench_time_cond;

	// PART I

	Datagrid* simpleArena;
	int people;

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
	Simulation(unsigned int people, int four_threads_cond, int bench_time_cond);
	std::vector<Entity*> get_vPersonnes();
	void start();
	bool isRunning();
};

#endif