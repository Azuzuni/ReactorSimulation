#pragma once

#include "ecs/entt/EnTTEcs.hpp"
#include "utils/Configuration.hpp"
#include <utility>
namespace ecs {

template<typename... Args>
inline util::Entity EnTTEcs::CreateImpl(Args&&...) {
  return static_cast<util::Entity>(mRegistry.create());
}

template <typename Component, typename... Args>
inline Component &EnTTEcs::AddImpl(util::Entity entity, Args &&...args) {
  return mRegistry.emplace<Component>(static_cast<util::Entity>(entity),
                                      std::forward<Args>(args)...);
}

template <typename... Components, typename Lambda>
inline void EnTTEcs::EachImpl(Lambda &&lambda) {
  auto view = mRegistry.view<Components...>();
  view.each([&](auto entity, Components &...comps) {
    lambda(static_cast<util::Entity>(entity), comps...);
  });
}

}; // namespace ecs
