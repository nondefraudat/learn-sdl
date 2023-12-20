#pragma once

#include "exchanges.hpp"

class App {
	App() noexcept;

public:
	~App() noexcept;

	static App& getInstance() noexcept;

	void setWindowSize(const size_t width,
			const size_t height) noexcept;

	bool init() noexcept;
	int exec() noexcept;

private:
	
	bool hasProblems, needInit;
	size_t width, height;
	
	Window window;
	Renderer renderer;

	void eventLoop() noexcept;
};
