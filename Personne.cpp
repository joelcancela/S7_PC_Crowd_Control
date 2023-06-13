#include "Personne.h"

Personne::Personne(int position_x, int position_y, std::queue<Command *> path) {
    this->pos_x = position_x;
    this->pos_y = position_y;

    this->size_x = PERSONNE_SIZE_X;
    this->size_y = PERSONNE_SIZE_Y;

    this->pathCommands = path;
}

Personne::~Personne() {
}

bool Personne::has_escaped() {
    return escaped;
}

Entity *Personne::getNextDestination(Datagrid *grid) {
    if (this->pathCommands.empty()) {
        return nullptr;
    }
    Command *c = this->pathCommands.front();
    if (c != nullptr) {
        return grid->getEntityAt(get_x() + c->x_modifier, get_y() + c->y_modifier);
    }
    return nullptr;
}

void Personne::move() {

    if (this->pathCommands.empty()) {
        return;
    }

    Command *c = this->pathCommands.front();

    if (c != nullptr) {
        if (c->exec(this->get_x(), this->get_y())) {
            this->pathCommands.pop();

            // Test if we have escaped
            if (Command::is_an_escape_zone(this->get_x(), this->get_y())) {
                this->escaped = true;
            }
        }
    }
    //sleep(1);
}

std::string Personne::to_string() {

    std::string s = "Personne {";

    s += std::to_string(this->get_x());
    s += ", ";
    s += std::to_string(this->get_y());
    s += "}";

    return s;
}