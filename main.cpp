#include <SDL3/SDL.h>
#include <cstdio>

int main(int argc, char* args[]) {
	const size_t screenWidth = 640;
	const size_t screenHeight = 480;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return NULL;
	}
	
	SDL_Window* const window = SDL_CreateWindow(
			"The Window!", screenWidth, screenHeight, NULL);
	if (!window) {
		return NULL;
	}

	SDL_Surface* const surface = SDL_GetWindowSurface(window);
	if (!surface) {
		return NULL;
	}

	SDL_FillSurfaceRect(surface, nullptr,
			SDL_MapRGB(surface->format, 255, 255, 255));

	SDL_UpdateWindowSurface(window);

	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT)
				quit = true;
		}
	}

	return NULL;
}