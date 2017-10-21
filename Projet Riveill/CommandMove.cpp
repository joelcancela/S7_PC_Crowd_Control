#include "CommandMove.h"

// North-West
void CommandNW::exec(int x, int y) {

	int shifted_x = x - 1;
	int shifted_y = y - 1;

	this->shared_exec(x, y, shifted_x, shifted_y);
}

// North
void CommandN::exec(int x, int y) {

	int shifted_x = x;
	int shifted_y = y - 1;

	this->shared_exec(x, y, shifted_x, shifted_y);
}

// West
void CommandW::exec(int x, int y) {

	int shifted_x = x - 1;
	int shifted_y = y;

	this->shared_exec(x, y, shifted_x, shifted_y);
}
