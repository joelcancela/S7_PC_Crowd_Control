#pragma once

#include "Command.h"

// North-West
class CommandNW : public Command {
public:
	CommandNW();
	~CommandNW();

	void exec();
};

// North
class CommandN : public Command {
public:
	CommandN();
	~CommandN();

	void Execute();
};

// West
class CommandW : public Command {
public:
	CommandW();
	~CommandW();

	void Execute();
};
