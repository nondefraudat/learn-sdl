#pragma once

#include "exchanges.hpp"
#include <string>

class TextureLoader {
	TextureLoader() noexcept;

public:
	~TextureLoader() noexcept;

	static TextureLoader& getInstance() noexcept;

	Texture load(const std::string& path,
			const Renderer& renderer) const noexcept;

private:
	bool hasProblems;
};
