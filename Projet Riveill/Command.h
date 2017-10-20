#pragma once

#include "Datagrid.h"

/*
* The Command interface.
*/
class Command {
public:
	virtual ~Command();
	virtual void exec() = 0;
protected:
	Datagrid* modelHandle;
	Command(Datagrid*);
};
