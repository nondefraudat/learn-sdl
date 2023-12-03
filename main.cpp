#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <cstdio>

struct Media {
	SDL_Texture* noactions = nullptr;
	SDL_Texture* xaction = nullptr;
	SDL_Texture* keyup = nullptr;
	SDL_Texture* keydown = nullptr;
	SDL_Texture* keyleft = nullptr;
	SDL_Texture* keyright = nullptr;
	SDL_Texture* example = nullptr;
};

const size_t screenWidth = 400;
const size_t screenHeight = 400;

SDL_Window* window = nullptr;
SDL_Surface* surface = nullptr;
SDL_Renderer* renderer = nullptr;

Media media;

bool init();
SDL_Surface* loadSurface(const char* path);
SDL_Texture* loadTexture(const char* path);
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

	SDL_Texture* texture = ::media.noactions;

	while (quit == false) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
			else if (e.type == SDL_EVENT_KEY_DOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP: {
						texture = ::media.keyup;
						break;
					}
					case SDLK_DOWN: {
						texture = ::media.keydown;
						break;
					}
					case SDLK_LEFT: {
						texture = ::media.keyleft;
						break;
					}
					case SDLK_RIGHT: {
						texture = ::media.keyright;
						break;
					}
					case SDLK_SPACE: {
						texture = ::media.example;
						break;
					}
					default: {
						texture = ::media.xaction;
						break;
					}
				}
			}
			else if (e.type == SDL_EVENT_KEY_UP) {
				texture = ::media.noactions;
			}
		}

		SDL_UpdateWindowSurface(::window);

		SDL_RenderClear(::renderer);
		SDL_RenderTexture(::renderer, texture, nullptr, nullptr);

		SDL_RenderPresent(::renderer);
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

	::renderer = SDL_CreateRenderer(::window,
			nullptr, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		return false;
	}

	SDL_SetRenderDrawColor(::renderer, 255, 255, 255, 255);

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

SDL_Texture* loadTexture(const char* path) {
	SDL_Surface* const buffer = loadSurface(path);
	if (!buffer) {
		return nullptr;
	}
	SDL_Texture* const texture = SDL_CreateTextureFromSurface(
			::renderer, buffer);
	SDL_DestroySurface(buffer);
	return texture;
}

bool loadMedia() {
	::media.noactions = loadTexture("rsc/noactions.bmp");
	::media.xaction = loadTexture("rsc/xaction.bmp");
	::media.keyup = loadTexture("rsc/keyup.bmp");
	::media.keydown = loadTexture("rsc/keydown.bmp");
	::media.keyleft = loadTexture("rsc/keyleft.bmp");
	::media.keyright = loadTexture("rsc/keyright.bmp");
	::media.example = loadTexture("rsc/example.png");
	return ::media.noactions && ::media.xaction &&
			::media.keyup && ::media.keydown &&
			::media.keyleft && ::media.keyright && ::media.example;
}

void close() {
	SDL_DestroyTexture(::media.noactions);
	SDL_DestroyTexture(::media.xaction);
	SDL_DestroyTexture(::media.keyup);
	SDL_DestroyTexture(::media.keydown);
	SDL_DestroyTexture(::media.keyleft);
	SDL_DestroyTexture(::media.keyright);
	SDL_DestroyTexture(::media.example);

	SDL_DestroyRenderer(::renderer);
	SDL_DestroyWindow(::window);

	IMG_Quit();
	SDL_Quit();
}


