#include <SDL3/SDL.h>
#include <cstdio>

struct Media {
	SDL_Surface* noactions = nullptr;
	SDL_Surface* xaction = nullptr;
	SDL_Surface* keyup = nullptr;
	SDL_Surface* keydown = nullptr;
	SDL_Surface* keyleft = nullptr;
	SDL_Surface* keyright = nullptr;
};

const size_t screenWidth = 640;
const size_t screenHeight = 480;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;

Media media;

bool init();
bool loadMedia();
void close();

int main(int argc, char* args[]) {
	if (!init()) {
		return NULL;
	}

	if (!loadMedia()) {
		auto e = SDL_GetError();
		return NULL;
	}

	SDL_Event e;
	bool quit = false;
	SDL_Surface* currentSurface = ::media.noactions;

	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_EVENT_KEY_DOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP: {
						currentSurface = ::media.keyup;
						break;
					}
					case SDLK_DOWN: {
						currentSurface = ::media.keydown;
						break;
					}
					case SDLK_LEFT: {
						currentSurface = ::media.keyleft;
						break;
					}
					case SDLK_RIGHT: {
						currentSurface = ::media.keyright;
						break;
					}
					default: {
						currentSurface = ::media.xaction;
						break;
					}
				}
			}
			else if (e.type == SDL_EVENT_KEY_UP) {
				currentSurface = ::media.noactions;
			}
		}

		SDL_BlitSurface(currentSurface, NULL, ::surface, NULL);
		SDL_UpdateWindowSurface(::window);
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
	::media.noactions = SDL_LoadBMP("rsc/noactions.bmp");
	::media.xaction = SDL_LoadBMP("rsc/xaction.bmp");
	::media.keyup = SDL_LoadBMP("rsc/keyup.bmp");
	::media.keydown = SDL_LoadBMP("rsc/keydown.bmp");
	::media.keyleft = SDL_LoadBMP("rsc/keyleft.bmp");
	::media.keyright = SDL_LoadBMP("rsc/keyright.bmp");
	return ::media.noactions && ::media.xaction && ::media.keyup &&
			::media.keydown && ::media.keyleft && ::media.keyright;
}

void close() {
	SDL_DestroySurface(::media.noactions);
	SDL_DestroySurface(::media.xaction);
	SDL_DestroySurface(::media.keyup);
	SDL_DestroySurface(::media.keydown);
	SDL_DestroySurface(::media.keyleft);
	SDL_DestroySurface(::media.keyright);

	SDL_DestroyWindow(::window);
	SDL_Quit();
}


