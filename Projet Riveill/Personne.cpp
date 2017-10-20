#include "Personne.h"

Personne::Personne(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;

	// Compute escape path
	// This is our command factory
}

Personne::~Personne()
{
}

std::string Personne::to_string() {
	return "*";
}

bool Personne::has_escaped() {

	// Top-Left
	if (this->pos_x == -1 && this->pos_y == -1) {
		return true;
	}
	// Top
	if (this->pos_x == 0 && this->pos_y == -1) {
		return true;
	}
	// Top-Right
	if (this->pos_x == 1 && this->pos_y == -1) {
		return true;
	}
	// Left
	if (this->pos_x == -1 && this->pos_y == 0) {
		return true;
	}
	// Bottom-Left
	if (this->pos_x == -1 && this->pos_y == 1) {
		return true;
	}

	return false;
}

// Return old position
std::vector<int> Personne::move() {

	std::vector<int> old_pos(2);
	old_pos[0] = this->get_x();
	old_pos[1] = this->get_y();
	return old_pos;
}