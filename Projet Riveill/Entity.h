#pragma once

#include "shared_header.h"

class Entity
{
protected:
	// Size of the entity
	unsigned int size_x = 0;
	unsigned int size_y = 0;

	// Position of the entity
	unsigned int pos_x = 0;
	unsigned int pos_y = 0;

public:
	virtual ~Entity() = 0;

	// Getters
	unsigned int get_x();
	unsigned int get_y();

	unsigned int get_size_x();
	unsigned int get_size_y();

protected:
	Entity();
};

