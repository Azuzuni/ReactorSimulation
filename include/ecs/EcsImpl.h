/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once

#if defined(kECSImplementation_entt)
#include "ecs/entt/EnTTEcs.hpp"
namespace ecs {
using Impl = ecs::EnTTEcs;
};
#else
#error "Undefined / Defined backend is incorrect."
#endif
