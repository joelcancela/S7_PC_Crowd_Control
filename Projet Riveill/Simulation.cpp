#include "Simulation.h"

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond)
{
	this->people = people;
	this->four_threads_cond = four_threads_cond;
	this->bench_time_cond = bench_time_cond;
	// Update simulation properties

	// Initialize obstacles
	// max{x=459, y=114}
	// min{x=10, y=10}
	Obstacle* o = new Obstacle(10, 10);
	this->obstacles.push_back(o);
	this->fill_grid(o);

	o = new Obstacle(76, 75);
	this->obstacles.push_back(o);
	this->fill_grid(o);

	o = new Obstacle(230, 64);
	this->obstacles.push_back(o);
	this->fill_grid(o);

	o = new Obstacle(459, 50);
	this->obstacles.push_back(o);
	this->fill_grid(o);

	o = new Obstacle(150, 114);
	this->obstacles.push_back(o);
	this->fill_grid(o);

	// Initialize personnes
	int x, y;
	for (int i = 0; i < people; i++) {
		Personne* p;

		// while we have not found a proper cell for our personne
		while (1) {
			x = rand() % GRID_SIZE_X;
			y = rand() % GRID_SIZE_Y;

			if (!this->dataGrid[x][y]) {
				p = new Personne(x, y);
				this->personnes.push_back(p);
				this->fill_grid(p);
				break;
			}
		}
	}
}

void Simulation::fill_grid(Entity* e) {
	std::vector<unsigned int> pos(2);
	pos[0] = e->get_x();
	pos[1] = e->get_y();

	std::vector<unsigned int> size(2);
	size[0] = e->get_size_x();
	size[1] = e->get_size_y();

	for (unsigned int x = 0; x < size[0]; ++x) {
		for (unsigned int y = 0; y < size[1]; ++y) {
			this->dataGrid[pos[0] + x][pos[1] + y] = true;
		}
	}
}

Simulation::~Simulation()
{
	// Clean obstacles
	for (unsigned int i = 0; i < this->obstacles.size(); i++) {
		delete this->obstacles[i];
	}

	// Clean personnes
	for (unsigned int i = 0; i < this->personnes.size(); i++) {
		delete this->personnes[i];
	}
}

std::vector<Entity*> Simulation::get_vObstacles() {
	return this->obstacles;
}

std::vector<Entity*> Simulation::get_vPersonnes() {
	return this->personnes;
}