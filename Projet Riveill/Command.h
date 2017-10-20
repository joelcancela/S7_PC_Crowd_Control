#pragma once

#include "Datagrid.h"
#include "Personne.h"

/*
* The Command interface.
*/
class Command {
public:
	virtual ~Command();
	virtual void exec() = 0;
protected:
	Datagrid* modelHandle;
	Personne* personneHandle;
	Command(Datagrid*, Personne*);
};
