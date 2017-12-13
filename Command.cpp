#include "Command.h"

bool Command::shared_exec(int x, int y, int shifted_x, int shifted_y, Datagrid *subject) {

	// fetch entity pointer
	Entity* e = subject->getEntityAt(x, y);
	if (e == nullptr) {
		return false; // This should never happen
	}

	// test if the new point is an escape zone
	if (is_an_escape_zone(shifted_x, shifted_y)) {

		// set person properties (out of the zone)
		e->set_x(shifted_x);
		e->set_y(shifted_y);
		
		// remove from the dataModel
		subject->setEntityAt(x, y, nullptr);
		return true;
	}

	// test if the shifted point is available
	if (subject->getEntityAt(shifted_x, shifted_y) != nullptr) {
		return false;
	}
	if (is_oob(shifted_x, shifted_y)) {
		return false;
	}

	// update entity properties
	e->set_x(shifted_x);
	e->set_y(shifted_y);

	// move entity to the new position
	subject->setEntityAt(x, y, nullptr);
	subject->setEntityAt(shifted_x, shifted_y, e);
	return true;
}

bool Command::exec(int x, int y, Datagrid *subject) {
	std::vector<int> dest = this->getNextPos(x, y);
	return this->shared_exec(x, y, dest[0], dest[1], subject);
}

bool Command::is_an_escape_zone(int x, int y) {

	// Top-Left
	if (x == -1 && y == -1) {
		return true;
	}
	// Top
	if (x == 0 && y == -1) {
		return true;
	}
	// Top-Right
	if (x == 1 && y == -1) {
		return true;
	}
	// Left
	if (x == -1 && y == 0) {
		return true;
	}
	// Bottom-Left
	if (x == -1 && y == 1) {
		return true;
	}

	return false;
}

bool Command::is_oob(int x, int y) {
	if (x < 0 || y < 0) {
		return true;
	}
	return false;
}

// North-West
std::vector<int> CommandNW::getNextPos(int x, int y) {
	std::vector<int> r(2);
	r[0] = x - 1;
	r[1] = y - 1;
	return r;
}

// North
std::vector<int> CommandN::getNextPos(int x, int y) {
	std::vector<int> r(2);
	r[0] = x;
	r[1] = y - 1;
	return r;
}

// West
std::vector<int> CommandW::getNextPos(int x, int y) {
	std::vector<int> r(2);
	r[0] = x - 1;
	r[1] = y;
	return r;
}
