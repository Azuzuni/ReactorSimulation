/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once



#if defined (kRenderingBackend_raylib)
#include "rendering/raylib/RaylibRender.hpp"
using RenderBackend = RaylibRender;
#else 
#error "Defined backend is incorrect."
#endif 
