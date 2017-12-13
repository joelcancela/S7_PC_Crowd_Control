#ifndef DATAGRID_H
#define DATAGRID_H

#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Personne.h"

class Datagrid {

private:

	// Grid absolute origin point
	unsigned origin_x = 0;
	unsigned origin_y = 0;

	// Spacial container
	Entity* dataGrid[GRID_SIZE_X][GRID_SIZE_Y] = { nullptr };

	/* List of contents */
	std::vector<Entity*> personnes;	// Personnes handler
	Obstacle* obstacle;				// Obstacle handle

public:
	Datagrid(unsigned origin_x, unsigned int origin_y, unsigned int seed, unsigned int people) {

		// Set grid origin
		this->origin_x = origin_x;
		this->origin_y = origin_y;

		// Initialize Obstacle position
		switch (seed) {
			case 10:
			case 20:
			case 32:
			case 48:
			case 64:
				obstacle = new Obstacle(seed + origin_x, seed + origin_y);
				break;
			default:
				obstacle = new Obstacle(32 + origin_x, 32 + origin_y);
		}
		this->fill_grid(obstacle);

		// Initialize People
		// people is the number of people to distribute over the grid
		int x, y;
		for (int i = 0; i < people; i++) {

			Personne *p;

			// while we have not found a proper cell for this personne
			while (true) {
				x = rand() % GRID_SIZE_X;
				y = rand() % GRID_SIZE_Y;

				if (this->dataGrid[x][y] == nullptr) {

					// Create new Personne
					p = new Personne(x + origin_x, y + origin_y, this);

					this->personnes.push_back(p);
					this->dataGrid[x][y] = p;
					break;
				}
			}
		}
	}

	/**
	 * Set entity at an absolute position among the grids
	 *
	 * @param x
	 * @param y
	 * @param e
	 */
	void setEntityAt(int x, int y, Entity* e) {

		// Patch real coordinates
		x -= this->origin_x;
		y -= this->origin_y;

		if (x >= 0 && y >= 0) {
			dataGrid[x][y] = e;
		}
	}

	/**
	 * Get entity at an absolute position among the grids
	 *
	 * @param x
	 * @param y
	 * @param e
	 */
	Entity* getEntityAt(int x, int y) {

		// Patch real coordinates
		x -= this->origin_x;
		y -= this->origin_y;

		if (x >= 0 && y >= 0) {
			return dataGrid[x][y];
		}
		return nullptr;
	}

private:

	/**
	 * Synchro between the grid and the entity position & size
	 */
	void fill_grid(Entity *e) {
		std::vector<int> pos(2);
		pos[0] = e->get_x();
		pos[1] = e->get_y();

		std::vector<unsigned int> size(2);
		size[0] = e->get_size_x();
		size[1] = e->get_size_y();

		for (unsigned int x = 0; x < size[0]; ++x) {
			for (unsigned int y = 0; y < size[1]; ++y) {
				this->setEntityAt(pos[0] + x, pos[1] + y, e);
			}
		}
	}
};

#endif