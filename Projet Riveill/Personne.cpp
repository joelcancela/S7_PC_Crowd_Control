#include "Personne.h"

Personne::Personne(int position_x, int position_y, std::stack<Command*> path)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;

	this->pathCommands = path;
}

Personne::~Personne(){
}

bool Personne::has_escaped() {
	return escaped;
}

void Personne::move() {

	if (this->pathCommands.empty()) {
		return;
	}

	Command* c = this->pathCommands.top();

	if (c != nullptr) {
		if (c->exec(this->get_x(), this->get_y())) {
			this->pathCommands.pop();

			// Test if we have escaped
			if (Command::isOOB(this->get_x(), this->get_y())) {
				this->escaped = true;
			}
		}
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