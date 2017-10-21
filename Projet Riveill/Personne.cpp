#include "Personne.h"

Personne::Personne(int position_x = 0, int position_y = 0)
{
	this->pos_x = position_x;
	this->pos_y = position_y;

	this->size_x = PERSONNE_SIZE_X;
	this->size_y = PERSONNE_SIZE_Y;

	// Compute azimuth (exit point)
	this->set_azimuth();
	
	// Compute path to escape point
	std::stack<Command*> iCommands; // Commands are in reverse order
}

Personne::~Personne(){
}

/**
* Compute shortest escape path
*/
void Personne::set_azimuth() {
	
	// Sorted list of azimuth
	std::map<double, std::vector<int>> azimuthSort;

	// List of escape points
	std::stack<std::vector<int>> vEscapePoints;

	std::vector<int> exitA(2); // {0, -1}
	exitA[0] = 0;
	exitA[1] = -1;
	std::vector<int> exitB(2); // {1, -1}
	exitB[0] = 1;
	exitB[1] = -1;
	std::vector<int> exitC(2); // {-1, 0}
	exitC[0] = -1;
	exitC[1] = 0;
	std::vector<int> exitD(2); // {-1, 1}
	exitD[0] = -1;
	exitD[1] = 1;

	vEscapePoints.push(exitA);
	vEscapePoints.push(exitB);
	vEscapePoints.push(exitC);
	vEscapePoints.push(exitD);

	while (!vEscapePoints.empty()) {
		
		std::vector<int> p(2); // Point
		p = vEscapePoints.top();
		vEscapePoints.pop();

		std::vector<int> v(2); // Vector

		// Compute vector
		v[0] = p[0] - this->pos_x;
		v[1] = p[1] - this->pos_y;

		// Compute length
		double size = sqrt(v[0] * v[0] + v[1] * v[1]);

		// Add to sorted list
		azimuthSort.insert(std::pair<double, std::vector<int>>(size, p));
	}

	// Set shortest point as azimuth
	std::map<double, std::vector<int>>::iterator it = azimuthSort.begin();
	for (it = azimuthSort.begin(); it != azimuthSort.end(); ++it) {
		this->azimuth = it->second;
		break;
	}
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
		if (c->exec(this->get_x(), this->get_size_y())) {
			this->commands.pop();

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