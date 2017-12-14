#include "shared_header.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Cell.h"

#ifndef DATAGRID_H
#define DATAGRID_H

class Datagrid {

private:

	// Grid absolute origin point
	unsigned origin_x = 0;
	unsigned origin_y = 0;

	// Spacial container
	Cell* dataGrid[GRID_SIZE_X][GRID_SIZE_Y] = { nullptr };

	/* List of contents */
	std::vector<Entity*> personnes;	// Personnes handler
	Obstacle* obstacle;				// Obstacle handle

public:
	Datagrid(unsigned int, unsigned int, unsigned int, unsigned int, int);

	/**
	 * Set entity at an absolute position among the grids
	 *
	 * @param x
	 * @param y
	 * @param e
	 */
	void setEntityAt(int, int, Entity*);

	/**
	 * Get entity at an absolute position among the grids
	 *
	 * @param x
	 * @param y
	 * @param e
	 */
	Entity* getEntityAt(int, int);

    /**
     * Gets the current number of personnes associated to this grid
     * @return
     */
    std::vector<Entity *> get_vPersonnes();

private:

	/**
	 * Synchro between the grid and the entity position & size
	 */
	void fill_grid(Entity *);
};

#endif