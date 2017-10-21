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
	virtual void exec(int, int) = 0;		// Compute new position
	void shared_exec(int, int, int, int);	// Update position in the dataModel
	bool static isOOB(int, int);			// Check if the position is out of bound (from the dataModel)
protected:
	Command(Datagrid*);
};
