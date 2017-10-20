#pragma once

#include "Command.h"

// North-West
class CommandNW : public Command {
public:
	void exec();
};

// North
class CommandN : public Command {
public:
	void exec();
};

// West
class CommandW : public Command {
public:
	void exec();
};
