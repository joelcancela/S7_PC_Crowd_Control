#pragma once

#include "shared_header.h"
#include "Command.h"

#define PERSONNE_SIZE_X 1
#define PERSONNE_SIZE_Y 1

class Personne : public Entity
{
private:
	std::stack<Command*> commands;
	bool escaped = false;
public:
	Personne(int position_x, int position_y);
	~Personne();

	bool has_escaped();
	void move();
	std::string to_string();
};
