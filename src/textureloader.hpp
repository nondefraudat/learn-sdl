#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <filesystem>

using TexturePtr = std::shared_ptr<class Texture>;

class TextureLoader {
public:
	~TextureLoader() noexcept;

	TextureLoader& getInstance() noexcept;

	TexturePtr load(const std::filesystem::path& path) noexcept;

private:
	TextureLoader() noexcept;
};

class Texture {
public:

};
