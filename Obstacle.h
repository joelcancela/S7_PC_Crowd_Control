#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "shared_header.h"
#include "Entity.h"

#define OBSTACLE_SIZE_REDUCTION_FACTOR 10

class Obstacle : public Entity
{

public:
	Obstacle(int position_x, int position_y);
	~Obstacle();

	std::string to_string();
};

#endif