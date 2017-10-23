#include "Command.h"

Command::Command(Datagrid* g) {
	this->modelHandle = g;
}

Command::~Command() {}

CommandNW::CommandNW(Datagrid* g) : Command(g) {
}

CommandN::CommandN(Datagrid* g) : Command(g) {
}

CommandW::CommandW(Datagrid* g) : Command(g) {
}

CommandN::~CommandN() {}
CommandNW::~CommandNW() {}
CommandW::~CommandW() {}

bool Command::shared_exec(int x, int y, int shifted_x, int shifted_y) {

	// fetch entity pointer
	Entity* e = this->modelHandle->getEntityAt(x, y);
	if (e == nullptr) {
		return false; // This should never happen
	}

	// test if the new point is an escape zone
	if (is_an_escape_zone(shifted_x, shifted_y)) {

		// set person properties (out of the zone)
		e->set_x(shifted_x);
		e->set_y(shifted_y);
		
		// remove from the dataModel
		this->modelHandle->setEntityAt(x, y, nullptr);
		return true;
	}

	// test if the shifted point is available
	if (this->modelHandle->getEntityAt(shifted_x, shifted_y) != nullptr) {
		return false;
	}
	if (is_oob(shifted_x, shifted_y)) {
		return false;
	}

	// update entity properties
	e->set_x(shifted_x);
	e->set_y(shifted_y);

	// move entity to the new position
	this->modelHandle->setEntityAt(x, y, nullptr);
	this->modelHandle->setEntityAt(shifted_x, shifted_y, e);
	return true;
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
bool CommandNW::exec(int x, int y) {
	return this->shared_exec(x, y, x - 1, y - 1);
}

// North
bool CommandN::exec(int x, int y) {
	return this->shared_exec(x, y, x, y - 1);
}

// West
bool CommandW::exec(int x, int y) {
	return this->shared_exec(x, y, x - 1, y);
}
