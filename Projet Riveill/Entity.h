#pragma once

#include "shared_header.h"

class Entity
{
protected:
	// Size of the entity
	int size_x = 0;
	int size_y = 0;

	// Position of the entity
	int pos_x = 0;
	int pos_y = 0;

public:
	Entity();
	~Entity();

	// Representation
	virtual std::string to_string() = 0; // Pure virtual function makes
                                         // this class Abstract class.

	// Getters
	std::vector<int>& get_position() {
		std::vector<int> position(2);
		position[0] = this->pos_x;
		position[1] = this->pos_y;
		return position;
	}

	std::vector<int>& get_size() {
		std::vector<int> size(2);
		size[0] = this->size_x;
		size[1] = this->size_y;
		return size;
	}
};

