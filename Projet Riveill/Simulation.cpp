#include "Simulation.h"

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond)
{
	// Update simulation properties
	this->people = people;
	this->four_threads_cond = four_threads_cond;
	this->bench_time_cond = bench_time_cond;

	this->dataGrid = new Datagrid();

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

			if (this->dataGrid->getEntityAt(x,y) == nullptr) {
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
			this->dataGrid->setEntityAt(pos[0] + x, pos[1] + y, e);
		}
	}
}

Simulation::~Simulation()
{
	// Clean obstacles
	this->obstacles.clear();

	// Clean personnes
	this->personnes.clear();
}

std::vector<Entity*> Simulation::get_vObstacles() {
	return this->obstacles;
}

std::vector<Entity*> Simulation::get_vPersonnes() {
	return this->personnes;
}

bool Simulation::isRunning() {
	return (this->get_vPersonnes().size() > 0) ? true : false;
}

// Compute the next frame
void Simulation::tick() {

	if (this->get_vPersonnes().size() == 0) {
		return;
	}

	// Move each personne to the escape zone
	std::vector<Entity*>::iterator it;
	for (it = this->personnes.begin(); it != this->personnes.end();) {

		Personne* p = dynamic_cast<Personne*>(*it);
		std::vector<int> old_pos;
		
		// Apply action
		p->move();

		// If someone has reached the escape zone, remove it from the list
		if (p->has_escaped()) {
			
			// rm from list
			// Fetch next valid iterator
			it = this->personnes.erase(it);
			
			// delete personne
			delete p;
		}
		else {
			it++; // Fetch next element in the list
		}
	}
}