#pragma once

/*
* The Command interface.
*/
class Command {
public:
	virtual ~Command();
	virtual void exec() = 0;
protected:
	Command();
};
