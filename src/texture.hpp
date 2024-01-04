#pragma once

#include "exchanges.hpp"
#include <memory>

class Texture {
    std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)> raw;
public:
    Texture(decltype(raw)&& raw) noexcept;
    void render(const Renderer& renderer) const noexcept;
    void render(SDL_Renderer* const renderer) const noexcept;
};
