#pragma once

#include "shared_header.h"
#include "Entity.h"

class Datagrid {

private:
	Entity* dataGrid[GRID_SIZE_X][GRID_SIZE_Y] = { nullptr }; // Model

public:
	Datagrid() {
	}

	~Datagrid() {
	}

	void setEntityAt(int x, int y, Entity* e) {
		if (x > 0 && y > 0) {
			dataGrid[x][y] = e;
		}
	}

	Entity* getEntityAt(int x, int y) {
		if (x > 0 && y > 0) {
			return dataGrid[x][y];
		}
	}
};