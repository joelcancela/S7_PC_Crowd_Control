#pragma once

#include "shared_header.h"
#include "Entity.h"

#define PERSONNE_SIZE_X 1
#define PERSONNE_SIZE_Y 1

class Personne : public Entity
{

public:
	Personne(int position_x, int position_y);
	~Personne();

	std::string to_string();
	bool has_escaped();
	std::vector<int> move();
};

