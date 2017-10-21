#pragma once

#include "Command.h"

// Pass position to alter

// North-West
class CommandNW : public Command {
public:
	void exec(int, int);
};

// North
class CommandN : public Command {
public:
	void exec(int, int);
};

// West
class CommandW : public Command {
public:
	void exec(int, int);
};
