#pragma once

#if defined(ECS_entt)
#include "ecs/entt/Implementation.hpp"
//! @brief backend implementation selection
//!        Current ecs backend: entt
namespace ecs {
using Impl = ecs::EnTTEcs;
};
#else
#error "Undefined / Defined backend is incorrect."
#endif
