#include "Obstacle.h"

Obstacle::Obstacle(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	// Random size generation on constructor
	this->size_x = rand() % (GRID_SIZE_X / OBSTACLE_SIZE_REDUCTION_FACTOR);
	this->size_x = rand() % (GRID_SIZE_Y / OBSTACLE_SIZE_REDUCTION_FACTOR);
}

Obstacle::~Obstacle()
{
}

std::string Obstacle::to_string() {
	return "#";
}
