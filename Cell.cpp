//
// Created by user on 14/12/17.
//

#include "Cell.h"

Cell::Cell(Entity *e) {
    this->wrapped_entity = e;
    pthread_mutex_trylock(this->mutex);
}

Entity *Cell::getEntity() {
    return this->wrapped_entity;
}

void Cell::setEntity(Entity *e) {
    this->wrapped_entity = e;
}

pthread_cond_t *Cell::getCond() {
    return this->cond;
}

pthread_mutex_t *Cell::getMutex() {
    return this->mutex;
}
