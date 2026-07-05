/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once

#if defined(RENDERING_raylib)
#include "rendering/raylib/Implementation.hpp"
//! @brief backend implementation selection
//!        Current render backend: raylib
using RenderBackend = RaylibRender;
#elif defined(RENDERING_sfml)
#include "rendering/sfml/Implementation.hpp"
//! @brief backend implementation selection
//!        Current render backend: sfml
using RenderBackend = SfmlRender;
#else
#error "Undefined / Defined backend is incorrect."
#endif
