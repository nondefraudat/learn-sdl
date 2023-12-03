#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
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
SDL_Surface* loadSurface(const char* path);
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

	SDL_Rect stretchRect {
		0, 0,
		::screenWidth,
		::screenHeight
	};
	SDL_Surface* currentSurface = ::media.noactions;
	SDL_Surface* pngSurface = loadSurface("rsc/example.png");

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
					case SDLK_SPACE: {
						currentSurface = pngSurface;
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

		SDL_BlitSurfaceScaled(currentSurface, NULL,
				::surface, &stretchRect);
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

	const int imageFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imageFlags) & imageFlags)) {
		return false;
	}

	::surface = SDL_GetWindowSurface(::window);

	return true;
}

SDL_Surface* loadSurface(const char* path) {
	SDL_Surface* const buffer = IMG_Load(path);
	if (!buffer) {
		return nullptr;
	}
	SDL_Surface* const surface = SDL_ConvertSurface(
		buffer, ::surface->format);
	SDL_DestroySurface(buffer);
	return surface;
}

bool loadMedia() {
	::media.noactions = loadSurface("rsc/noactions.bmp");
	::media.xaction = loadSurface("rsc/xaction.bmp");
	::media.keyup = loadSurface("rsc/keyup.bmp");
	::media.keydown = loadSurface("rsc/keydown.bmp");
	::media.keyleft = loadSurface("rsc/keyleft.bmp");
	::media.keyright = loadSurface("rsc/keyright.bmp");
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


