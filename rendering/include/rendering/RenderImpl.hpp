/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once

#if defined(RENDERING_raylib)
#include "rendering/raylib/Implementation.hpp"
using RenderBackend = RaylibRender;
#elif defined(RENDERING_sfml)
#include "rendering/sfml/SfmlRender.h"
using RenderBackend = SfmlRender;
#else
#error "Undefined / Defined backend is incorrect."
#endif
