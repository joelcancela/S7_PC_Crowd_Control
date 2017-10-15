#include "shared_header.h"
#include "Simulation.h"

#define ZOOM_FACTOR 2
#define W_WIDTH  ((GRID_SIZE_X * ZOOM_FACTOR) + (2 * ZOOM_FACTOR))
#define W_HEIGHT ((GRID_SIZE_Y * ZOOM_FACTOR) + (2 * ZOOM_FACTOR))

/*
We double the model size in order to have something more visible for the end-user.
Moreover, we add a border of 2px to the scene
*/

int main(int argc, char *argv[])
{
	// Var repository
	bool end_of_simulation = false;				// Main loop

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
		W_WIDTH,
		W_HEIGHT,
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
	SDL_SetRenderDrawColor(renderer, 117, 11, 28, 255);
	// UP
	int i;
	for (i = 0; i < W_WIDTH; ++i) {
		SDL_RenderDrawPoint(renderer, i, 0);
		SDL_RenderDrawPoint(renderer, i, 1);
	}
	// DOWN
	for (i = 0; i < W_WIDTH; ++i) {
		SDL_RenderDrawPoint(renderer, i, W_HEIGHT - 1);
		SDL_RenderDrawPoint(renderer, i, W_HEIGHT - 2);
	}
	// LEFT
	for (int i = 0; i < W_HEIGHT; ++i) {
		SDL_RenderDrawPoint(renderer, 0, i);
		SDL_RenderDrawPoint(renderer, 1, i);
	}
	// RIGHT
	for (int i = 0; i < W_HEIGHT; ++i) {
		SDL_RenderDrawPoint(renderer, W_WIDTH - 1, i);
		SDL_RenderDrawPoint(renderer, W_WIDTH - 2, i);
	}
	SDL_RenderPresent(renderer);

	// Start simulation
	Simulation* simu = new Simulation();
	while (!end_of_simulation) {

		// Quit by event
		if (SDL_PollEvent(&sdl_event)) {
			if (sdl_event.type == SDL_QUIT) {
				end_of_simulation = true;
			}
		}

		// Give us time to see the window changes.
		SDL_Delay(10);

		// Update screen rendering
		SDL_RenderPresent(renderer);
	}

	// End Of Simulation
	delete simu;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return EXIT_SUCCESS;
}
