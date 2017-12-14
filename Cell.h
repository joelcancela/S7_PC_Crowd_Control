//
// Created by nikita on 14/12/17.
//

#ifndef CROWDCONTROL_CELL_H
#define CROWDCONTROL_CELL_H


#include <zconf.h>
#include <pthread.h>
#include "Entity.h"

class Cell {

    Entity* wrapped_entity = nullptr;

    pthread_mutex_t *mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t *cond = PTHREAD_COND_INITIALIZER;

public:
    explicit Cell(Entity*);
    /**
     * Get entity
     *
     * @param x
     * @param y
     * @param e
     */
    Entity* getEntity();
    /**
     * Set entity
     *
     * @param x
     * @param y
     * @param e
     */
    void setEntity(Entity*);
    /**
     * Get pthread_cond_t
     * @return
     */
    pthread_cond_t* getCond();
    /**
     * Get pthread_cond_t
     * @return
     */
    pthread_mutex_t* getMutex();
};

#endif //CROWDCONTROL_CELL_H
