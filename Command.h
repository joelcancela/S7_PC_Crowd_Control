#ifndef COMMAND_H
#define COMMAND_H

#include "Datagrid.h"

/**
 * The Command interface
 * must be implemented by each command
 */

class Command {

protected:

	/**
	 * Apply on the underlying datagrid (i.e, move the entity to another cell)
	 * Update position in the dataModel : return true if success, false otherwise
	 *
	 * src / dest / subject
	 *
	 * @return
	 */
	bool shared_exec(int, int, int, int, Personne*, Datagrid*);

public:

	/**
	 * Combined calls of getNextPos() and shared_exec()
	 *
	 * return true if success, false otherwise
	 *
	 * @param subject
	 * @return bool
	 */
	virtual bool exec(int, int, Personne*, Datagrid*);

	/**
	 * Compute new position from given position
	 *
	 * @return std::vector<int>
	 */
	virtual std::vector<int> getNextPos(int, int) = 0;

	/**
	 * Check if the given position is a valid escape position
	 *
	 * @return bool
	 */
	static bool is_an_escape_zone(int, int);

	/**
	 * Check if the given position is out of bound (from the dataModel)
	 *
	 * @return
	 */
	static bool is_oob(int, int);
};

// North-West
class CommandNW : public Command {
public:
	std::vector<int> getNextPos(int, int) override;
};

// North
class CommandN : public Command {
public:
	std::vector<int> getNextPos(int, int) override;
};

// West
class CommandW : public Command {
public:
	std::vector<int> getNextPos(int, int) override;
};

#endif