#include "Simulation.h"

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond)
{
	// Update simulation properties
	this->people = people;
	this->four_threads_cond = four_threads_cond;
	this->bench_time_cond = bench_time_cond;

	this->dataGrid = new Datagrid();

	// Initialize obstacles
	//
	// Constraints:
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
		// while we have not found a proper cell for this personne
		while (1) {
			x = rand() % GRID_SIZE_X;
			y = rand() % GRID_SIZE_Y;

			if (this->dataGrid->getEntityAt(x,y) == nullptr) {

				// Compute Azimuth
				std::vector<int> az = azimuth(x, y);

				// Compute Path
				std::stack<Command*> pa = path(x, y, az);

				// Create new Personne
				p = new Personne(x, y, pa);

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


/**
 * Compute shortest escape point from the given position
 */
std::vector<int> Simulation::azimuth(int pos_x, int pos_y) {

	// Sorted list of azimuth
	std::map<double, std::vector<int>> azimuthSort;

	// List of escape points
	std::stack<std::vector<int>> vEscapePoints;

	std::vector<int> exitA(2); // {0, -1}
	exitA[0] = 0;
	exitA[1] = -1;
	std::vector<int> exitB(2); // {1, -1}
	exitB[0] = 1;
	exitB[1] = -1;
	std::vector<int> exitC(2); // {-1, 0}
	exitC[0] = -1;
	exitC[1] = 0;
	std::vector<int> exitD(2); // {-1, 1}
	exitD[0] = -1;
	exitD[1] = 1;

	vEscapePoints.push(exitA);
	vEscapePoints.push(exitB);
	vEscapePoints.push(exitC);
	vEscapePoints.push(exitD);

	while (!vEscapePoints.empty()) {

		// Point
		std::vector<int> p(2);
		p = vEscapePoints.top();
		vEscapePoints.pop();

		// Vector
		std::vector<int> v(2);

		// Compute vector
		v[0] = p[0] - pos_x;
		v[1] = p[1] - pos_y;

		// Compute length
		double size = sqrt(v[0] * v[0] + v[1] * v[1]);

		// Add to sorted list
		azimuthSort.insert(std::pair<double, std::vector<int>>(size, p));
	}

	// Set shortest point as azimuth
	std::map<double, std::vector<int>>::iterator it = azimuthSort.begin();
	for (it = azimuthSort.begin(); it != azimuthSort.end(); ++it) {
		return it->second;
	}
}

/**
 * Compute shortest escape path
 */
std::stack<Command*> Simulation::path(int pos_x, int pos_y, std::vector<int> azimuth)
{
	// Commands stack
	std::stack<Command*> path;
	std::stack<Command*> iPath;

	// Sorted list of distances
	std::map<double, Command*> pathSort;

	// Commands
	CommandN* mv_n = new CommandN(this->dataGrid);
	CommandNW* mv_nw = new CommandNW(this->dataGrid);
	CommandW* mv_w = new CommandW(this->dataGrid);

	while (1) {

		// if we have reached the escape point
		// break, we have finished
		if (pos_x == azimuth[0] && pos_y == azimuth[1]) {
			break;
		}

		// Flush selector
		pathSort.clear();

		// Compute the three posibilities
		// Only if the next position is not blocked by an Obstacle

		// north
		std::vector<int> n = this->getNextPos(mv_n, pos_x, pos_y);
		if (dynamic_cast<Obstacle*>(this->dataGrid->getEntityAt(n[0], n[1])) == nullptr) {
			double len_n = sqrt(
				(azimuth[0] - n[0]) * (azimuth[0] - n[0]) +
				(azimuth[1] - n[1]) * (azimuth[1] - n[1])
			);
			pathSort.insert(std::pair<double, Command*>(len_n, mv_n));
		}

		// north-west
		std::vector<int> nw = this->getNextPos(mv_nw, pos_x, pos_y);
		if (dynamic_cast<Obstacle*>(this->dataGrid->getEntityAt(nw[0], nw[1])) == nullptr) {
			double len_nw = sqrt(
				(azimuth[0] - nw[0]) * (azimuth[0] - nw[0]) +
				(azimuth[1] - nw[1]) * (azimuth[1] - nw[1])
			);
			pathSort.insert(std::pair<double, Command*>(len_nw, mv_nw));
		}
		
		// west
		std::vector<int> w = this->getNextPos(mv_w, pos_x, pos_y);
		if (dynamic_cast<Obstacle*>(this->dataGrid->getEntityAt(w[0], w[1])) == nullptr) {
			double len_w = sqrt(
				(azimuth[0] - w[0]) * (azimuth[0] - w[0]) +
				(azimuth[1] - w[1]) * (azimuth[1] - w[1])
			);
			pathSort.insert(std::pair<double, Command*>(len_w, mv_w));
		}

		// Pick the command that brings us closer to the azimuth
		std::map<double, Command*>::iterator it = pathSort.begin();
		for (it = pathSort.begin(); it != pathSort.end(); ++it) {

			Command* c = it->second;
			iPath.push(c);

			// Update {x, y} for the next iteration
			std::vector<int> next_pos(2);

			if (dynamic_cast<CommandN*>(c) != nullptr) {
				next_pos = this->getNextPos(dynamic_cast<CommandN*>(c), pos_x, pos_y);
			}
			else if (dynamic_cast<CommandNW*>(c) != nullptr) {
				next_pos = this->getNextPos(dynamic_cast<CommandNW*>(c), pos_x, pos_y);
			}
			else {
				next_pos = this->getNextPos(dynamic_cast<CommandW*>(c), pos_x, pos_y);
			}

			pos_x = next_pos[0];
			pos_y = next_pos[1];

			break;
		}
	}

	// Reverse stack
	while (!iPath.empty()) {
		path.push(iPath.top());
		iPath.pop();
	}

	return path;
}

std::vector<int> Simulation::getNextPos(CommandN* n, int x, int y) {
	std::vector<int> r(2);
	r[0] = x;
	r[1] = y - 1;
	return r;
}

std::vector<int> Simulation::getNextPos(CommandNW* nw, int x, int y) {
	std::vector<int> r(2);
	r[0] = x - 1;
	r[1] = y - 1;
	return r;
}
std::vector<int> Simulation::getNextPos(CommandW* w, int x, int y) {
	std::vector<int> r(2);
	r[0] = x - 1;
	r[1] = y;
	return r;
}