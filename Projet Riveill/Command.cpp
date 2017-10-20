#include "Command.h"

Command::Command(Datagrid* g, Personne* p) {
	this->modelHandle = g;
	this->personneHandle = p;
}
Command::~Command() {}
