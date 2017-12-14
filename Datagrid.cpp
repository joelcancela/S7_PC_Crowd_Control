#include "Datagrid.h"
#include "Personne.h"

Datagrid::Datagrid(int origin_x, int origin_y, int seed, int people, int shapeRatio) {

    // Set grid origin
    this->origin_x = origin_x;
    this->origin_y = origin_y;

    for (int i = 0; i < (GRID_SIZE_X); i++) {
        for (int j = 0; j < (GRID_SIZE_Y); j++) {
            dataGrid[i][j] = new Cell();
        }
    }

    // Initialize Obstacle position
    switch (seed) {
        case 10:
        case 20:
        case 32:
        case 48:
            obstacle = new Obstacle(seed + origin_x, seed + origin_y);
            break;
        default:
            obstacle = new Obstacle(32 + origin_x, 32 + origin_y);
    }
    this->fill_grid(obstacle);

    // Initialize People
    // people is the number of people to distribute over the grid
    int x, y;
    for (int i = 0; i < people; i++) {

        Personne *p;

        // while we have not found a proper cell for this personne
        while (true) {
            x = rand() % (GRID_SIZE_X / shapeRatio);
            y = rand() % (GRID_SIZE_Y / shapeRatio);

            if (this->dataGrid[x][y]->isEmpty()) {

                // Create new Personne
                p = new Personne(x + origin_x, y + origin_y, this);

                this->personnes.push_back(p);
                this->dataGrid[x][y]->setEntity(p);
                break;
            }
        }
    }
}

void Datagrid::setEntityAt(int x, int y, Entity* e) {

    // Patch real coordinates
    x -= this->origin_x;
    y -= this->origin_y;

    if (x >= 0 && y >= 0) {
        dataGrid[x][y]->setEntity(e);
    }
}


Entity* Datagrid::getEntityAt(int x, int y) {

    // Patch real coordinates
    x -= this->origin_x;
    y -= this->origin_y;

    if (x >= 0 && y >= 0) {
        return dataGrid[x][y]->getEntity();
    }
    return nullptr;
}

Cell *Datagrid::getCellAt(int x, int y) {

    // Patch real coordinates
    x -= this->origin_x;
    y -= this->origin_y;

    if (x >= 0 && y >= 0) {
        return dataGrid[x][y];
    }
    return nullptr;
}

std::vector<Entity *> Datagrid::get_vPersonnes() {
    return this->personnes;
}

void Datagrid::fill_grid(Entity *e) {
    std::vector<int> pos(2);
    pos[0] = e->get_x();
    pos[1] = e->get_y();

    std::vector< int> size(2);
    size[0] = e->get_size_x();
    size[1] = e->get_size_y();

    for ( int x = 0; x < size[0]; ++x) {
        for ( int y = 0; y < size[1]; ++y) {
            this->setEntityAt(pos[0] + x, pos[1] + y, e);
        }
    }
}

int Datagrid::getOrigin_x() const {
    return origin_x;
}

int Datagrid::getOrigin_y() const {
    return origin_y;
}
