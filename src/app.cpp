#include "app.hpp"
#include "textureloader.hpp"
#include <cmath>

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

void App::updateView() noexcept {
	// Test actions
	
	static const SDL_Rect viewPort = {
		std::round(.05*height),
		std::round(.05*height),
		std::round(width - .1*height),
		std::round(.9*height)
	};
	static Texture texture = TextureLoader::getInstance()
			.load("rsc/example.png", renderer);

	SDL_RenderClear(renderer.get());
	SDL_SetRenderViewport(renderer.get(), &viewPort);
	SDL_RenderTexture(renderer.get(), texture.get(), nullptr, nullptr);
	SDL_RenderPresent(renderer.get());
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
		updateView();
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
	SDL_SetRenderDrawColor(renderer.get(), 0, 0, 255, 255);
	needInit = true;
	return true;
}
