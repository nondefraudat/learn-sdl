#include "app.hpp"
#include "textureloader.hpp"

App::App() noexcept : width(640), height(480),
		window(nullptr, SDL_DestroyWindow),
		renderer(nullptr, SDL_DestroyRenderer) {
	hasProblems = (SDL_Init(SDL_INIT_VIDEO) < 0);
	needInit = !hasProblems;
}

App::~App() noexcept {
	renderer.reset();
	window.reset();
	if (!hasProblems) {
		SDL_Quit();
	}
}

App& App::getInstance() noexcept {
	static App instance;
	return instance;
}

void App::setWindowSize(
		const size_t width, const size_t height) noexcept {
	this->width = width;
	this->height = height;
	needInit = false;
}

int App::exec() noexcept {
	if (needInit) {
		init();
	}
	eventLoop();
	return 0;
}

void App::eventLoop() noexcept {
	SDL_Event e;
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}
		SDL_RenderClear(renderer.get());
		SDL_RenderPresent(renderer.get());
	}
}

bool App::init() noexcept {
	window.reset(SDL_CreateWindow("SDL Samples", width, height, NULL));
	if (!window) {
		return false;
	}
	renderer.reset(SDL_CreateRenderer(window.get(), nullptr,
			SDL_RENDERER_ACCELERATED));
	if (!renderer) {
		return false;
	}
	SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
	needInit = true;
	return true;
}
