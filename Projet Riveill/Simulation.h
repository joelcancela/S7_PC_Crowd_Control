

#include <mutex>
#include "shared_header.h"
#include "Entity.h"
#include "Datagrid.h"
#include "Personne.h"
#include "Obstacle.h"

class Simulation
{
	double people;
	int four_threads_cond;
	int bench_time_cond;

	Datagrid* dataGrid;
    std::vector<Entity*> personnes;
	std::vector<Entity*> obstacles;

public:
	Simulation(double people, int four_threads_cond, int bench_time_cond);
	~Simulation();
	void fill_grid(Entity* e);
	std::vector<Entity*> get_vObstacles();
	std::vector<Entity*> get_vPersonnes();
	void start();
	bool isRunning();
};

