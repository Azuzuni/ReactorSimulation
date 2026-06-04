/**
 * @file
 * @brief Compiletime selection for rendering backend
 */

#pragma once

#if defined(ECS_entt)
#include "ecs/entt/Implementation.hpp"
namespace ecs {
using Impl = ecs::EnTTEcs;
};
#else
#error "Undefined / Defined backend is incorrect."
#endif
