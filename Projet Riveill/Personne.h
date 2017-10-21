#pragma once

#include "shared_header.h"
#include "Command.h"

#define PERSONNE_SIZE_X 1
#define PERSONNE_SIZE_Y 1

class Personne : public Entity
{
private:
	std::stack<Command*> pathCommands;
	bool escaped = false;

public:
	Personne(int, int, std::stack<Command*>);
	~Personne();
	std::string to_string();
	bool has_escaped();
	void move();
};
