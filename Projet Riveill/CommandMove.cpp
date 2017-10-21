#include "CommandMove.h"

// North-West
bool CommandNW::exec(int x, int y) {

	int shifted_x = x - 1;
	int shifted_y = y - 1;

	return this->shared_exec(x, y, shifted_x, shifted_y);
}

// North
bool CommandN::exec(int x, int y) {

	int shifted_x = x;
	int shifted_y = y - 1;

	return this->shared_exec(x, y, shifted_x, shifted_y);
}

// West
bool CommandW::exec(int x, int y) {

	int shifted_x = x - 1;
	int shifted_y = y;

	return this->shared_exec(x, y, shifted_x, shifted_y);
}
