#ifndef PERSONNE_H
#define PERSONNE_H

#include "Entity.h"
#include "Datagrid.h"

#define PERSONNE_SIZE_X 1
#define PERSONNE_SIZE_Y 1

class Personne : public Entity
{

private:
	// Has escaped the ARENA ?
	bool escaped = false;

	// On which grid the personne is associated ?
	Datagrid* datagrid = nullptr;

public:
	Personne(int, int, Datagrid*);
	/**
	 * Computes the coordinates of the next hop
	 * @return
	 */
	std::vector<int> getNextDestination();
	/**
	 * Gets escape attribute
	 * @return
	 */
	bool has_escaped();
	/**
	 * Triggers the move
	 */
	void move();
	/**
	 * Gets string representation of the personne
	 * @return
	 */
	std::string to_string();
	/**
	 * Gets grid
	 */
	Datagrid *getDatagrid();
	/**
	 * Change grid
	 */
	void updateGrid(Datagrid*);
};

#endif