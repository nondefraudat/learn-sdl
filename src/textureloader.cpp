#include "textureloader.hpp"

TextureLoader::TextureLoader() noexcept {
	const auto imageFlags = IMG_INIT_PNG;
	hasProblems = !(IMG_Init(imageFlags) & imageFlags);
}

TextureLoader::~TextureLoader() noexcept {
	if (!hasProblems) {
		IMG_Quit();
	}
}

TextureLoader& TextureLoader::getInstance() noexcept {
	static TextureLoader instance;
	return instance;
}

Texture TextureLoader::load(const std::string& path,
		const Renderer& renderer) const noexcept {
	Texture texture(nullptr, SDL_DestroyTexture);
	Surface surface(IMG_Load(path.c_str()), SDL_DestroySurface);
	if (!surface) {
		return texture;
	}
	texture.reset(
			SDL_CreateTextureFromSurface(renderer.get(), surface.get()));
	return texture;
}
