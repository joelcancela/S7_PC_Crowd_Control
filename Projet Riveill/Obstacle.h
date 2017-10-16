#pragma once

#include "shared_header.h"
#include "Entity.h"
#include "Simulation.h"

#define OBSTACLE_SIZE_REDUCTION_FACTOR 8

class Obstacle : public Entity
{

public:
	Obstacle(unsigned int position_x, unsigned int position_y);
	~Obstacle();

	std::string to_string();
};

