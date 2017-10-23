#pragma once

#include "Datagrid.h"

/*
* The Command interface.
*/
class Command {
protected:
	Datagrid* modelHandle;
public:
	Command(Datagrid*);
	virtual ~Command();
	virtual bool exec(int, int) = 0;					// Compute new position from current position : return true if success, false otherwise
	bool shared_exec(int, int, int, int);				// Update position in the dataModel : return true if success, false otherwise
	static bool is_an_escape_zone(int, int);			// Check if the given position is a valid escape position
	static bool is_oob(int, int);						// Check if the position is out of bound (from the dataModel)
};

// North-West
class CommandNW : public Command {
public:
	CommandNW(Datagrid*);
	~CommandNW();
	bool exec(int, int);
};

// North
class CommandN : public Command {
public:
	CommandN(Datagrid*);
	~CommandN();
	bool exec(int, int);
};

// West
class CommandW : public Command {
public:
	CommandW(Datagrid*);
	~CommandW();
	bool exec(int, int);
};
