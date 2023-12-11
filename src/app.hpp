#pragma once

#include "textureloader.hpp"
#include <SDL3/SDL.h>

class App {
public:
	~App() noexcept;

	static App& getInstance() noexcept;

private:
	static constexpr size_t windowWidth = 640;
	static constexpr size_t windowHeight = 480;

	SDL_Window* windot = nullptr;
	SDL_Surface* surface = nullptr;
	SDL_Renderer* renderer = nullptr;
	TextureLoader textureLoader;

	App() noexcept;

	void init() noexcept;
};