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
	Entity();
	~Entity();

	// Representation
	virtual std::string to_string() = 0; // Pure virtual function makes
                                         // this class Abstract class.

	// Getters
	unsigned int Entity::get_x();
	unsigned int Entity::get_y();

	unsigned int Entity::get_size_x();
	unsigned int Entity::get_size_y();
};

