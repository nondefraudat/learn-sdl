#include "app.hpp"

App::~App() noexcept {
	if (renderer) {
		SDL_DestroyRenderer(renderer);
	}
	if (surface) {
		SDL_DestroySurface(surface);
	}
	if (window) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
}

App& App::getInstance() noexcept {
	static App instance;
	return instance;
}

App::App() noexcept {
	init();
}

void App::init() noexcept {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return;
	}
	window = SDL_CreateWindow("SDL Samples",
			windowWidth, windowHeight, NULL);
	if (!window) {
		return;
	}
	surface = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window,
			nullptr, SDL_RENDERER_ACCELERATED);
}
