#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

// Getters
int Entity::get_x() {
	return this->pos_x;
}
int Entity::get_y() {
	return this->pos_y;
}

 int Entity::get_size_x() {
	return this->size_x;
}
 int Entity::get_size_y() {
	return this->size_y;
}

// Setters
void Entity::set_x(int x) {
	this->pos_x = x;
}
void Entity::set_y(int y) {
	this->pos_y = y;
}