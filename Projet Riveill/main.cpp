#include <getopt.h>
#include <cmath>
#include "shared_header.h"
#include "Simulation.h"
#include "main.h"

#define ZOOM_FACTOR 1
#define W_WIDTH  (GRID_SIZE_X * ZOOM_FACTOR)
#define W_HEIGHT (GRID_SIZE_Y * ZOOM_FACTOR)

/**
 * SDL Drawer for frame / border of the scene
 */
void crowd_control_draw_borders(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 117, 11, 28, 255);

    // UP
    for (int i = 0; i < W_WIDTH + 4; ++i) {
        SDL_RenderDrawPoint(renderer, i, 0);
        SDL_RenderDrawPoint(renderer, i, 1);
    }
    // DOWN
    for (int i = 0; i < W_WIDTH + 4; ++i) {
        SDL_RenderDrawPoint(renderer, i, W_HEIGHT + 2);
        SDL_RenderDrawPoint(renderer, i, W_HEIGHT + 3);
    }
    // LEFT
    for (int i = 0; i < W_HEIGHT + 4; ++i) {
        SDL_RenderDrawPoint(renderer, 0, i);
        SDL_RenderDrawPoint(renderer, 1, i);
    }
    // RIGHT
    for (int i = 0; i < W_HEIGHT + 4; ++i) {
        SDL_RenderDrawPoint(renderer, W_WIDTH + 2, i);
        SDL_RenderDrawPoint(renderer, W_WIDTH + 3, i);
    }

    SDL_RenderPresent(renderer);
}

/**
 * SDL Drawer for the hostage escape zone
 */
void crowd_control_draw_escape_zone(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 11, 106, 11, 255);

    for (int i = 0; i < 4; ++i) {
        SDL_RenderDrawPoint(renderer, 0, i);
        SDL_RenderDrawPoint(renderer, 1, i);
    }
    for (int i = 0; i < 4; ++i) {
        SDL_RenderDrawPoint(renderer, i, 1);
        SDL_RenderDrawPoint(renderer, i, 0);
    }

    SDL_RenderPresent(renderer);
}

/**
 * SDL Drawer for obstacles
 */
void crowd_control_draw_obstacles(SDL_Renderer *renderer, Simulation *simulation) {
    SDL_SetRenderDrawColor(renderer, 73, 130, 5, 255);
    std::vector<Entity *> obstacles = simulation->get_vObstacles();

    for (unsigned int i = 0; i < obstacles.size(); ++i) {
        Obstacle o = (*dynamic_cast<Obstacle *>(obstacles[i]));    // Dereference of the object

        std::vector<unsigned int> pos(2);                            // Position of the obstacle on the grid
        pos[0] = o.get_x();
        pos[1] = o.get_y();

        std::vector<unsigned int> size(2);                            // Size of the obstacle
        size[0] = o.get_size_x();
        size[1] = o.get_size_y();

        for (unsigned int x = 0; x < size[0]; ++x) {
            for (unsigned int y = 0; y < size[1]; ++y) {
                SDL_RenderDrawPoint(renderer, pos[0] + x + 2, pos[1] + y + 2);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

/**
 * - We double the model size in order to have something more visible for the end-user.
 * - Moreover, we add a border of 2px to the scene
 * - Escape zone is 4px * 4px (we take in consideration the border of 2px)
 */

int main(int argc, char *argv[]) {
    int opt, bench_time = 0, four_threads = 0;
    double people = 1;
    while ((opt = getopt(argc, argv, "p:t:m")) != -1) {
        switch (opt) {
            case 'p':
                //std::cout << "Option p" << std::endl;
                people = pow(2.0, strtod(optarg, NULL));
                if (people < 1 || people > 512) {
                    std::cerr << "p must be between 0 & 9";
                    return 1;
                }
                //std::cout << people;
                break;
            case 't':
                //std::cout << "Option t" << optarg << std::endl;
                four_threads = atoi(optarg);
                if (four_threads < 0 || four_threads > 1) {
                    std::cerr << "t must be either 0 or 1";
                    return 1;
                }
                //std::cout<<four_threads;
                break;
            case 'm':
                //std::cout << "Option m" << std::endl;
                bench_time = atoi(optarg);
                break;
            default:
                break;
        }
    }

    // Var repository
    bool end_of_simulation = false;                // Main loop
    Simulation *simu = new Simulation(people, four_threads, bench_time);        // Simulation handle

    /* SDL */
    SDL_Window *win = nullptr;                    // Main SDL window
    SDL_Renderer *renderer = nullptr;

    SDL_Event sdl_event;                        // SDL events

    // SDL2 init
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "[FATAL] SDL2 init error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create main window
    win = SDL_CreateWindow(
            "Crowd control simulation",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            (W_WIDTH + 4),
            (W_HEIGHT + 4),
            0);
    if (win == 0) {
        std::cout << "[FATAL] SDL2 main window init error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create renderer
    renderer = SDL_CreateRenderer(
            win,
            -1,
            SDL_RENDERER_ACCELERATED);
    if (renderer == 0) {
        std::cout << "[FATAL] SDL2 renderer init error : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Initial screen color is black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);    // Back in black. #ACDCROCKS
    SDL_RenderClear(renderer);                        // Clear the current rendering target with the drawing color.
    SDL_RenderPresent(renderer);                    // Up until now everything was drawn behind the scenes.
    // This will show the new contents of the window.
    // Doc: update the screen with any rendering performed since the previous call.

    /* Draw borders */
    crowd_control_draw_borders(renderer);

    /* Draw escape zone #CSGO */
    crowd_control_draw_escape_zone(renderer);

    /* Draw obstacles */
    crowd_control_draw_obstacles(renderer, simu);

    while (!end_of_simulation) {

        // Quit by event
        if (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_QUIT) {
                end_of_simulation = true;
            }
        }

        // Draw people
        /*
        for (i = 0; i < GRID_SIZE_Y; i++) {
            for (j = 0; j < GRID_SIZE_Y; j++) {
                if (simu->get_matrix()[i][j] != nullptr) {
                    SDL_SetRenderDrawColor(renderer, 36, 36, 102, 255);
                    SDL_RenderDrawPoint(renderer, i, j);
                }
            }
        }
        */

        // Update screen rendering
        SDL_RenderPresent(renderer);

        // Give us time to see the window changes.
        SDL_Delay(100);
    }

    // End Of Simulation
    delete simu;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return EXIT_SUCCESS;
}
