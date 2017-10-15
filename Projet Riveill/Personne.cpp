#include "Personne.h"

Personne::Personne(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;
}

Personne::~Personne()
{
}

std::string Personne::to_string() {
	return "*";
}
