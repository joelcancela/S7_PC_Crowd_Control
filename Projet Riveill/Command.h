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
	virtual void exec() = 0;
protected:
	Command(Datagrid*);
};
