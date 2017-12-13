#include "Personne.h"

Personne::Personne(int position_x, int position_y, Datagrid* d) {
    this->pos_x = position_x;
    this->pos_y = position_y;

    this->size_x = PERSONNE_SIZE_X;
    this->size_y = PERSONNE_SIZE_Y;

    this->datagrid = d;
}

bool Personne::has_escaped() {
    return escaped;
}

std::vector<int> Personne::getNextDestination() {

    // CURRENT POS
    std::vector<int> pos(3);
    pos[0] = this->get_x();
    pos[1] = this->get_y();
    pos[2] = -1;

    // FUTURE NORTH
    std::vector<int> pos_n(3);
    pos_n[0] = this->get_x();
    pos_n[1] = this->get_y() - 1;
    pos_n[2] = 0;

    // FUTURE NW
    std::vector<int> pos_nw(3);
    pos_nw[0] = this->get_x() - 1;
    pos_nw[1] = this->get_y() - 1;
    pos_nw[2] = 1;

    // FUTURE W
    std::vector<int> pos_w(3);
    pos_w[0] = this->get_x() - 1;
    pos_w[1] = this->get_y();
    pos_w[2] = 2;

    // IF NORTH-WEST IS AVAILABLE
    if (!Command::is_oob(pos_nw[0], pos_nw[1]) && datagrid->getEntityAt(pos_nw[0], pos_nw[1]) == nullptr) {
        // GO NORTH-WEST
        return pos_nw;
    }

    // IF NORTH IS OUT OF ARENA or OCCUPIED
    if (Command::is_oob(pos_n[0], pos_n[1]) || (datagrid->getEntityAt(pos_n[0], pos_n[1]) != nullptr)) {

        if (datagrid->getEntityAt(pos_w[0], pos_w[1]) == nullptr) {
            // GO LEFT
            return pos_w;
        }
    }

    // IF WEST IS OUT OF ARENA or OCCUPIED
    if (Command::is_oob(pos_w[0], pos_w[1]) || (datagrid->getEntityAt(pos_w[0], pos_w[1]) != nullptr)) {

        if (datagrid->getEntityAt(pos_n[0], pos_n[1]) == nullptr) {
            // GO NORTH
            return pos_n;
        }
    }

    // STAY
    return pos;
}

void Personne::move() {

    Command c;

    std::vector<int> next = this->getNextDestination();

    switch (next[2]) {
        case 0:
            c = CommandN();
            break;
        case 1:
            c = CommandNW();
            break;
        case 2:
            c = CommandW();
            break;
        default:
        case -1:
            return;
    }

    c.exec(this->get_x(), this->get_y(), this, this->datagrid);

    // Test if we have escaped
    if (Command::is_an_escape_zone(this->get_x(), this->get_y())) {
        this->escaped = true;
    }
}

std::string Personne::to_string() {

    std::string s = "Personne {";

    s += std::to_string(this->get_x());
    s += ", ";
    s += std::to_string(this->get_y());
    s += "}";

    return s;
}

void Personne::updateGrid(Datagrid * d) {
    if (d == nullptr) {
        return;
    }
    this->datagrid = d;
}