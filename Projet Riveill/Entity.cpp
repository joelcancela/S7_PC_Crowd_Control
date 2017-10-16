#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

// Getters
unsigned int Entity::get_x() {
	return this->pos_x;
}
unsigned int Entity::get_y() {
	return this->pos_y;
}

unsigned int Entity::get_size_x() {
	return this->size_x;
}
unsigned int Entity::get_size_y() {
	return this->size_y;
}
