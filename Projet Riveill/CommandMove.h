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

// North-East
class CommandNE : public Command {
public:
	CommandNE();
	~CommandNE();

	void Execute();
};

// West
class CommandW : public Command {
public:
	CommandW();
	~CommandW();

	void Execute();
};

// EasT
class CommandE : public Command {
public:
	CommandE();
	~CommandE();

	void Execute();
};

// South-West
class CommandSW : public Command {
public:
	CommandSW();
	~CommandSW();

	void Execute();
};

// South
class CommandS : public Command {
public:
	CommandS();
	~CommandS();

	void Execute();
};

// South-East
class CommandSE : public Command {
public:
	CommandSE();
	~CommandSE();

	void Execute();
};

