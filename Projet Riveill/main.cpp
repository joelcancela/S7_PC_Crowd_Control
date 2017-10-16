#include "main.h"
#include "shared_header.h"
#include "Simulation.h"

#define ZOOM_FACTOR 1

#define W_WIDTH  (GRID_SIZE_X * ZOOM_FACTOR)
#define W_HEIGHT (GRID_SIZE_Y * ZOOM_FACTOR)

/**
 * SDL Drawer for frame / border of the scene
 */
void crowd_control_draw_borders(SDL_Renderer* renderer) {
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
 * Static zone, not affected by ZOOM
 */
void crowd_control_draw_escape_zone(SDL_Renderer* renderer) {
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
 * DRAW entities px by px
 */
void crowd_control_draw_entity(
	SDL_Renderer* renderer,
	Simulation* simulation,
	Entity* e) {

	std::vector<unsigned int> pos(2);	// Position of the obstacle on the grid
	pos[0] = e->get_x();
	pos[1] = e->get_y();

	std::vector<unsigned int> size(2);	// Size of the obstacle
	size[0] = e->get_size_x() * ZOOM_FACTOR;
	size[1] = e->get_size_y() * ZOOM_FACTOR;

	for (unsigned int x = 0; x < size[0]; ++x) {
		for (unsigned int y = 0; y < size[1]; ++y) {
			SDL_RenderDrawPoint(renderer, pos[0] + x + 2, pos[1] + y + 2);
		}
	}
}

/**
 * SDL Drawer for obstacles
 */
void crowd_control_draw_obstacles(SDL_Renderer* renderer, Simulation* simulation) {
	SDL_SetRenderDrawColor(renderer, 73, 130, 5, 255);
	std::vector<Entity*> obstacles = simulation->get_vObstacles();

	for (unsigned int i = 0; i < obstacles.size(); ++i) {
		crowd_control_draw_entity(renderer, simulation, obstacles[i]);
	}

	SDL_RenderPresent(renderer);
}

/**
 * SDL Drawer for personnes
 */
void crowd_control_draw_personnes(SDL_Renderer* renderer, Simulation* simulation) {
	SDL_SetRenderDrawColor(renderer, 36, 36, 102, 255);
	std::vector<Entity*> personnes = simulation->get_vPersonnes();

	for (unsigned int i = 0; i < personnes.size(); ++i) {
		crowd_control_draw_entity(renderer, simulation, personnes[i]);
	}

	SDL_RenderPresent(renderer);
}

/**
 * - We double the model size in order to have something more visible for the end-user.
 * - Moreover, we add a border of 2px to the scene
 * - Escape zone is 4px * 4px (we take in consideration the border of 2px)
 */

int main(int argc, char *argv[])
{
	// Var repository
	bool end_of_simulation = false;				// Main loop
	Simulation* simu = new Simulation(6);		// Simulation handle

	/* SDL */
	SDL_Window *win = nullptr;					// Main SDL window
	SDL_Renderer *renderer = nullptr;

	SDL_Event sdl_event;						// SDL events

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
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);	// Back in black. #ACDCROCKS
	SDL_RenderClear(renderer);						// Clear the current rendering target with the drawing color. 
	SDL_RenderPresent(renderer);					// Up until now everything was drawn behind the scenes.
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
		crowd_control_draw_personnes(renderer, simu);

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
