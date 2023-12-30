#include "texture.hpp"

Texture::Texture(decltype(raw)&& raw) noexcept
        : raw(std::move(raw)) { }

void Texture::render(SDL_Renderer *const renderer) const noexcept {
    SDL_RenderTexture(renderer, raw.get(), nullptr, nullptr);
}
