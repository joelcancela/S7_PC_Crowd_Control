#pragma once

#include "shared_header.h"

class Entity
{
protected:
	// Size of the entity
	unsigned int size_x = 0;
	unsigned int size_y = 0;

	// Position of the entity
	int pos_x = 0;
	int pos_y = 0;

public:
	virtual ~Entity() = 0;

	// Getters
	int get_x();
	int get_y();

	unsigned int get_size_x();
	unsigned int get_size_y();

	// Setters
	void set_x(int);
	void set_y(int);

protected:
	Entity();
};

