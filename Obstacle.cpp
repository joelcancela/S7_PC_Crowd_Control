#include "Obstacle.h"

Obstacle::Obstacle(int position_x, int position_y)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	// Random size generation on constructor
	this->size_x = rand() % (GRID_SIZE_X / OBSTACLE_SIZE_REDUCTION_FACTOR) + 1;
	this->size_y = rand() % (GRID_SIZE_Y / OBSTACLE_SIZE_REDUCTION_FACTOR) + 1;
}

Obstacle::~Obstacle()
{
}

std::string Obstacle::to_string() {
	return "#";
}
