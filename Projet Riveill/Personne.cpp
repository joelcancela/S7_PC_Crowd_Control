#include "Personne.h"

Personne::Personne(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;

	/**
	 * Compute shortest escape path
	 * This is our command factory
	 */

	// Compute shortest distance to the 4 exit points
	std::vector<int> exitA(2); // {0, -1}
	exitA[0] = (0) - this->pos_x;
	exitA[1] = (-1) - this->pos_y;
	float sizeA = (int)sqrt(exitA[0] * exitA[0] + exitA[1] * exitA[1]);
	std::vector<int> exitB(2); // {1, -1}
	exitB[0] = (1) - this->pos_x;
	exitB[1] = (-1) - this->pos_y;
	float sizeB = (int)sqrt(exitB[0] * exitB[0] + exitB[1] * exitB[1]);
	std::vector<int> exitC(2); // {-1, 0}
	exitC[0] = (-1) - this->pos_x;
	exitC[1] = (0) - this->pos_y;
	std::vector<int> exitD(2); // {-1, 1}
	exitC[0] = (-1) - this->pos_x;
	exitC[1] = (1) - this->pos_y;
	
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
void Personne::move() {

	if (this->commands.empty()) {
		return;
	}

	Command* c = this->commands.top();
	
	if (c != nullptr) {
		this->commands.pop();
		c->exec();
	}
}