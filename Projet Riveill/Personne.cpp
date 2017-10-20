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
	float sizeA = sqrt(exitA[0] * exitA[0] + exitA[1] * exitA[1]);
	std::vector<int> exitB(2); // {1, -1}
	exitB[0] = (1) - this->pos_x;
	exitB[1] = (-1) - this->pos_y;
	float sizeB = sqrt(exitB[0] * exitB[0] + exitB[1] * exitB[1]);
	std::vector<int> exitC(2); // {-1, 0}
	exitC[0] = (-1) - this->pos_x;
	exitC[1] = (0) - this->pos_y;
	float sizeC = sqrt(exitC[0] * exitC[0] + exitC[1] * exitC[1]);
	std::vector<int> exitD(2); // {-1, 1}
	exitC[0] = (-1) - this->pos_x;
	exitC[1] = (1) - this->pos_y;
	float sizeD = sqrt(exitD[0] * exitD[0] + exitD[1] * exitD[1]);
	
	std::stack<Command*> iCommands; // Commands are in reverse order
}

Personne::~Personne(){
}

bool Personne::has_escaped() {
	return escaped;
}

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

std::string Personne::to_string() {
	std::string s = "Personne {";
	s += std::to_string(this->get_x());
	s += ", ";
	s += std::to_string(this->get_y());
	s += "}";
	return s;
}