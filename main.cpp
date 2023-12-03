#include <SDL3/SDL.h>
#include <cstdio>

const size_t screenWidth = 640;
const size_t screenHeight = 480;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Surface* media = nullptr;

bool init();
bool loadMedia();
void close();

int main(int argc, char* args[]) {
	if (!init()) {
		return NULL;
	}

	if (!loadMedia()) {
		return NULL;
	}

	SDL_BlitSurface(::media, NULL, ::surface, NULL);
	SDL_UpdateWindowSurface(::window);

	SDL_Event e;
	bool quit = false;
	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT)
				quit = true;
		}
	}

	close();
	return NULL;
}

bool init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return false;
	}

	::window = SDL_CreateWindow("Hello World!",
		::screenWidth, ::screenHeight, NULL);
	if (!window) {
		return false;
	}

	::surface = SDL_GetWindowSurface(::window);

	return true;
}

bool loadMedia() {
	::media = SDL_LoadBMP("helloworld.bmp");
	return ::media != nullptr;
}

void close() {
	SDL_DestroySurface(::media);
	SDL_DestroyWindow(::window);
	SDL_Quit();
}


