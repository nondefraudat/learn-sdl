#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <memory>

using Window = std::unique_ptr<SDL_Window, void(*)(SDL_Window*)>;
using Surface = std::unique_ptr<SDL_Surface, void(*)(SDL_Surface*)>;
using Renderer = std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)>;
using Texture = std::unique_ptr<SDL_Texture, void(*)(SDL_Texture*)>;
