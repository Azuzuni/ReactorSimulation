/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once



#if defined (RENDERING_raylib)
#include "rendering/raylib/RaylibRender.h"
using RenderBackend = RaylibRender;
#else 
#error "Undefined / Defined backend is incorrect."
#endif 
