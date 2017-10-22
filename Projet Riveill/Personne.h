#pragma once

#include "shared_header.h"
#include "Command.h"

#define PERSONNE_SIZE_X 1
#define PERSONNE_SIZE_Y 1

class Personne : public Entity
{
private:
	std::queue<Command*> pathCommands;
	bool escaped = false;

public:
	Personne(int, int, std::queue<Command*>);
	~Personne();
	Entity* getNextDestination(Datagrid* grid);
	std::string to_string();
	bool has_escaped();
	void move();
};
