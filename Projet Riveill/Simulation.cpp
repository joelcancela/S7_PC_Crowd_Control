#include "Simulation.h"

void *tick(void *arguments);

static pthread_mutex_t simulation_mutex = PTHREAD_MUTEX_INITIALIZER;

struct arg_struct {
    Simulation *instance;
    int thread_number;
};

Simulation::Simulation(double people, int four_threads_cond, int bench_time_cond) {
    // Update simulation properties
    this->people = people;
    this->four_threads_cond = four_threads_cond;
    this->bench_time_cond = bench_time_cond;

    // Data model
    this->dataGrid = new Datagrid();

    // Initialize obstacles
    //
    // Constraints:
    // max{x=459, y=114}
    // min{x=10, y=10}
    Obstacle *o = new Obstacle(10, 10);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(76, 75);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(230, 64);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(459, 50);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    o = new Obstacle(150, 114);
    this->obstacles.push_back(o);
    this->fill_grid(o);

    // Initialize personnes
    int x, y;
    for (int i = 0; i < people; i++) {

        Personne *p;

        // while we have not found a proper cell for this personne
        while (1) {
            x = rand() % GRID_SIZE_X;
            y = rand() % GRID_SIZE_Y;

            if (this->dataGrid->getEntityAt(x, y) == nullptr) {

                // Compute Azimuth
                std::vector<int> az = azimuth(x, y);

                // Compute Path
                std::queue<Command *> pa = path(x, y, az);

                // Create new Personne
                p = new Personne(x, y, pa);
                this->personnes.push_back(p);
                this->fill_grid(p);
                break;
            }
        }
    }
}

void Simulation::fill_grid(Entity *e) {
    std::vector<int> pos(2);
    pos[0] = e->get_x();
    pos[1] = e->get_y();

    std::vector<unsigned int> size(2);
    size[0] = e->get_size_x();
    size[1] = e->get_size_y();

    for (unsigned int x = 0; x < size[0]; ++x) {
        for (unsigned int y = 0; y < size[1]; ++y) {
            this->dataGrid->setEntityAt(pos[0] + x, pos[1] + y, e);
        }
    }
}

// Compute the next frame
void *tick(void *arguments) {
    pthread_mutex_lock(&simulation_mutex);
    struct arg_struct *args = (struct arg_struct *) arguments;
    int nb = args->thread_number;
    Simulation *instance = args->instance;
    Personne *p = dynamic_cast<Personne *>(instance->get_vPersonnes()[nb]);
    pthread_mutex_unlock(&simulation_mutex);
    while (!p->has_escaped()) {
        pthread_mutex_lock(&simulation_mutex);
        p->move();
        std::cout << "Thread #" << nb << " id:" << pthread_self() << " a deplace " << p->to_string() << std::endl;
        pthread_mutex_unlock(&simulation_mutex);
        //usleep(100000);
    }
    std::cout << "!!!!!!!Thread #" << nb << " id:" << pthread_self() << " ma personne est sortie!!!!!!!" << std::endl;
    return NULL;
}

void create_thread(pthread_t thread_persons[], int i, Simulation *pSimulation) {
    auto *args = new arg_struct();
    args->instance = pSimulation;
    args->thread_number = i;
    int error = pthread_create(&thread_persons[i], NULL, &tick, (void *) args);
    if (error) {
        std::cout << "Error when creating threads";
    }
}

void Simulation::start() {
    if (four_threads_cond) {
        //TODO split
    } else {
        pthread_t thread_persons[(int) people];
        for (int i = 0; i < people; ++i) {
            create_thread(thread_persons, i, this);
        }
        for (int j = 0; j < people; j++) {
            pthread_join(thread_persons[j], NULL);
        }
        while(!get_vPersonnes().empty()){
            Personne *p = dynamic_cast<Personne *>(personnes[0]);
            personnes.erase(personnes.begin());
            delete p;
        }

    }
}

Simulation::~Simulation() {
    // Clean obstacles
    this->obstacles.clear();

    // Clean personnes
    this->personnes.clear();
}

std::vector<Entity *> Simulation::get_vObstacles() {
    return this->obstacles;
}

std::vector<Entity *> Simulation::get_vPersonnes() {
    return this->personnes;
}

bool Simulation::isRunning() {
    return (this->get_vPersonnes().size() > 0) ? true : false;
}

/**
 * Compute shortest escape point from the given position
 */
std::vector<int> Simulation::azimuth(int pos_x, int pos_y) {

    // Sorted list of azimuth
    std::map<double, std::vector<int>> azimuthSort;

    // List of escape points
    std::queue<std::vector<int>> vEscapePoints;

    std::vector<int> exitA(2); // {0, -1}
    exitA[0] = 0;
    exitA[1] = -1;
    std::vector<int> exitB(2); // {1, -1}
    exitB[0] = 1;
    exitB[1] = -1;
    std::vector<int> exitC(2); // {-1, 0}
    exitC[0] = -1;
    exitC[1] = 0;
    std::vector<int> exitD(2); // {-1, 1}
    exitD[0] = -1;
    exitD[1] = 1;

    vEscapePoints.push(exitA);
    vEscapePoints.push(exitB);
    vEscapePoints.push(exitC);
    vEscapePoints.push(exitD);

    while (!vEscapePoints.empty()) {

        // Point
        std::vector<int> p(2);
        p = vEscapePoints.front();
        vEscapePoints.pop();

        // Vector
        std::vector<int> v(2);

        // Compute vector
        v[0] = p[0] - pos_x;
        v[1] = p[1] - pos_y;

        // Compute length
        double size = sqrt(v[0] * v[0] + v[1] * v[1]);

        // Add to sorted list
        azimuthSort.insert(std::pair<double, std::vector<int>>(size, p));
    }

    // Set shortest point as azimuth
    std::map<double, std::vector<int>>::iterator it = azimuthSort.begin();
    for (it = azimuthSort.begin(); it != azimuthSort.end(); ++it) {
        return it->second;
    }

    return std::vector<int>(2, 0);
}

/**
 * Compute shortest escape path
 */
std::queue<Command *> Simulation::path(int pos_x, int pos_y, std::vector<int> azimuth) {
    // Commands stack
    std::queue<Command *> path;

    // Sorted list of distances
    std::map<double, Command *> pathSort;

    // Commands
    CommandN *mv_n = new CommandN(this->dataGrid);
    CommandNW *mv_nw = new CommandNW(this->dataGrid);
    CommandW *mv_w = new CommandW(this->dataGrid);

    while (1) {

        // if we have reached the escape point
        // break, we have finished
        if (pos_x == azimuth[0] && pos_y == azimuth[1]) {
            break;
        }

        // Flush selector
        pathSort.clear();

        // Compute the three posibilities
        // Only if the next position is not blocked by an Obstacle
        // OK for an escape, KO for border traversal

        // north
        std::vector<int> n = this->getNextPos(mv_n, pos_x, pos_y);
        if (dynamic_cast<Obstacle *>(this->dataGrid->getEntityAt(n[0], n[1])) == nullptr) {
            if (Command::is_an_escape_zone(n[0], n[1]) || !Command::is_oob(n[0], n[1])) {
                double len_n = sqrt(
                        (azimuth[0] - n[0]) * (azimuth[0] - n[0]) +
                        (azimuth[1] - n[1]) * (azimuth[1] - n[1])
                );
                pathSort.insert(std::pair<double, Command *>(len_n, mv_n));
            }
        }

        // north-west
        std::vector<int> nw = this->getNextPos(mv_nw, pos_x, pos_y);
        if (dynamic_cast<Obstacle *>(this->dataGrid->getEntityAt(nw[0], nw[1])) == nullptr) {
            if (Command::is_an_escape_zone(nw[0], nw[1]) || !Command::is_oob(nw[0], nw[1])) {
                double len_nw = sqrt(
                        (azimuth[0] - nw[0]) * (azimuth[0] - nw[0]) +
                        (azimuth[1] - nw[1]) * (azimuth[1] - nw[1])
                );
                pathSort.insert(std::pair<double, Command *>(len_nw, mv_nw));
            }
        }

        // west
        std::vector<int> w = this->getNextPos(mv_w, pos_x, pos_y);
        if (dynamic_cast<Obstacle *>(this->dataGrid->getEntityAt(w[0], w[1])) == nullptr) {
            if (Command::is_an_escape_zone(w[0], w[1]) || !Command::is_oob(w[0], w[1])) {
                double len_w = sqrt(
                        (azimuth[0] - w[0]) * (azimuth[0] - w[0]) +
                        (azimuth[1] - w[1]) * (azimuth[1] - w[1])
                );
                pathSort.insert(std::pair<double, Command *>(len_w, mv_w));
            }
        }

        // Pick the command that brings us closer to the azimuth
        std::map<double, Command *>::iterator it = pathSort.begin();
        for (it = pathSort.begin(); it != pathSort.end(); ++it) {

            Command *c = it->second;
            path.push(c);

            // Update {x, y} for the next iteration
            std::vector<int> next_pos(2);

            // N
            if (dynamic_cast<CommandN *>(c) != nullptr) {
                next_pos = this->getNextPos(dynamic_cast<CommandN *>(c), pos_x, pos_y);
            }
                // NW
            else if (dynamic_cast<CommandNW *>(c) != nullptr) {
                next_pos = this->getNextPos(dynamic_cast<CommandNW *>(c), pos_x, pos_y);
            }
                // W
            else {
                next_pos = this->getNextPos(dynamic_cast<CommandW *>(c), pos_x, pos_y);
            }

            pos_x = next_pos[0];
            pos_y = next_pos[1];

            break;
        }
    }

    return path;
}

std::vector<int> Simulation::getNextPos(CommandN *n, int x, int y) {
    std::vector<int> r(2);
    r[0] = x;
    r[1] = y - 1;
    return r;
}

std::vector<int> Simulation::getNextPos(CommandNW *nw, int x, int y) {
    std::vector<int> r(2);
    r[0] = x - 1;
    r[1] = y - 1;
    return r;
}

std::vector<int> Simulation::getNextPos(CommandW *w, int x, int y) {
    std::vector<int> r(2);
    r[0] = x - 1;
    r[1] = y;
    return r;
}
