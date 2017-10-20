#include "Personne.h"

Personne::Personne(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;

	// Compute shortest escape path
	// This is our command factory
	
	std::stack<Command*> iCommands; // Commands are in reverse order
}

Personne::~Personne(){
}

std::string Personne::to_string() {
	return "*";
}

bool Personne::has_escaped() {
	return escaped;
}

// Return old position when successful 
// TODO : Trigers exception otherwise
void Personne::move() {

	//Command* c = this->commands.top();
	//this->commands.pop();
	//c->exec();
}