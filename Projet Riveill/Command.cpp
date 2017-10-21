#include "Command.h"

Command::Command(Datagrid* g) {
	this->modelHandle = g;
}

Command::~Command() {}

void Command::shared_exec(int x, int y, int shifted_x, int shifted_y) {

	// test if the shifted point is available
	// do nothing otherwise
	if (this->modelHandle->getEntityAt(shifted_x, shifted_y) != nullptr) {
		return;
	}

	// fetch entity pointer
	Entity* e = this->modelHandle->getEntityAt(x, y);

	// update entity properties
	e->set_x(shifted_x);
	e->set_y(shifted_y);

	// test if the new point is out of bound
	if (isOOB(shifted_x, shifted_y)) {
		// person has escaped
		// remove from the dataModel
		this->modelHandle->setEntityAt(x, y, nullptr);
		return;
	}

	// move entity to the new position
	this->modelHandle->setEntityAt(x, y, nullptr);
	this->modelHandle->setEntityAt(shifted_x, shifted_y, e);
}

bool Command::isOOB(int x, int y) {

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

	// Position is not out of bound
	return false;
}