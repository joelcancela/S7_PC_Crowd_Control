#pragma once

#include "Datagrid.h"

/*
* The Command interface.
*/
class Command {
protected:
	Datagrid* modelHandle;
public:
	virtual ~Command();
	virtual bool exec(int, int) = 0;		// Compute new position from current position : return true if success, false otherwise
	bool shared_exec(int, int, int, int);	// Update position in the dataModel : return true if success, false otherwise
	static bool isOOB(int, int);			// Check if the position is out of bound (from the dataModel)
protected:
	Command(Datagrid*);
};
