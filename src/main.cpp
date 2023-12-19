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
	SDL_Texture* what = nullptr;
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
void drawTexture(SDL_Texture* texture);
void drawWhat();
void drawGeoms();
void close();

int main(int argc, char* args[]) {
	if (!init()) {
		auto e = SDL_GetError();
		return 0;
	}

	if (!loadMedia()) {
		auto e = SDL_GetError();
		return 0;
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
		SDL_RenderClear(::renderer);
		drawWhat();
		drawTexture(texture);
		drawGeoms();
		SDL_RenderPresent(::renderer);
	}

	close();
	return 0;
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
	SDL_SetSurfaceColorKey(buffer,
			SDL_TRUE, SDL_MapRGB(buffer->format, 29, 255, 0));
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

void drawTexture(SDL_Texture* texture) {
	static const SDL_Rect viewport{
		::screenWidth - 200,
		::screenHeight - 200,
		200, 200
	};

	//SDL_UpdateWindowSurface(::window);

	// Save prev viewport
	SDL_Rect rect;
	SDL_GetRenderViewport(::renderer, &rect);

	SDL_SetRenderViewport(::renderer, &viewport);
	SDL_RenderTexture(::renderer, texture, nullptr, nullptr);

	// Return prev viewport
	SDL_SetRenderViewport(::renderer, &rect);
}

void drawWhat() {
	static const SDL_Rect viewport {
		::screenWidth - 100, 0,
		100, 100
	};
	
	if (!::media.what) {
		SDL_Surface* buffer = loadSurface("rsc/what.bmp");

		if (!buffer) {
			return;
		}

		SDL_SetSurfaceColorKey(buffer, SDL_TRUE,
				SDL_MapRGB(buffer->format, 29, 255, 0));

		::media.what = SDL_CreateTextureFromSurface(::renderer, buffer);

		SDL_DestroySurface(buffer);

		if (!::media.what) {
			return;
		}
	}

	// Save prev viewport
	SDL_Rect rect;
	SDL_GetRenderViewport(::renderer, &rect);

	SDL_SetRenderViewport(::renderer, &viewport);
	SDL_RenderTexture(::renderer, ::media.what, nullptr, nullptr);

	// Return prev viewport
	SDL_SetRenderViewport(::renderer, &rect);
}

void drawGeoms() {
	static const SDL_FRect fillRect { 10, 10, 100, 100 };
	static const SDL_FRect rect { 50, 10, 100, 10 };
	
	// Save prev color;
	unsigned char r, g, b, a;
	SDL_GetRenderDrawColor(::renderer, &r, &g, &b, &a);

	SDL_SetRenderDrawColor(::renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(::renderer, &fillRect);

	SDL_SetRenderDrawColor(::renderer, 0, 255, 0, 255);
	SDL_RenderRect(::renderer, &rect);

	SDL_SetRenderDrawColor(::renderer, 0, 0, 255, 255);
	SDL_RenderLine(::renderer, 0, 0, ::screenWidth, ::screenHeight);

	SDL_SetRenderDrawColor(::renderer, 255, 0, 255, 255);
	// Dashed line
	for (size_t i = ::screenWidth, j = 0;
		j < ::screenHeight; i -= 6, j += 6) {
		SDL_RenderPoint(::renderer, i, j);
		SDL_RenderPoint(::renderer, i - 1, j + 1);
		SDL_RenderPoint(::renderer, i - 2, j + 2);
	}

	// Return prev color;
	SDL_SetRenderDrawColor(::renderer, r, g, b, a);
}

void close() {
	SDL_DestroyTexture(::media.noactions);
	SDL_DestroyTexture(::media.xaction);
	SDL_DestroyTexture(::media.keyup);
	SDL_DestroyTexture(::media.keydown);
	SDL_DestroyTexture(::media.keyleft);
	SDL_DestroyTexture(::media.keyright);
	SDL_DestroyTexture(::media.example);
	SDL_DestroyTexture(::media.what);

	SDL_DestroyRenderer(::renderer);
	SDL_DestroyWindow(::window);

	IMG_Quit();
	SDL_Quit();
}


