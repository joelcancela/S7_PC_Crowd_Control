//
// Created by user on 14/12/17.
//

#include "Cell.h"

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

bool Cell::isEmpty() {
    return this->wrapped_entity == nullptr;
}
