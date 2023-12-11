#include "textureloader.hpp"

TextureLoader::~TextureLoader() noexcept {
	IMG_Quit();
}

TextureLoader& TextureLoader::getInstance() noexcept {
	static TextureLoader instance;
	return instance;
}

TextureLoader::TextureLoader() noexcept {
	IMG_Init(IMG_INIT_PNG)
}
