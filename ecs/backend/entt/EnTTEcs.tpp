#pragma once

#include "ecs/entt/EnTTEcs.hpp"
#include "entt/entity/fwd.hpp"
#include "utils/Configuration.hpp"
#include <utility>
namespace ecs {

inline util::Entity EnTTEcs::CreateImpl() {
  return static_cast<util::Entity>(mRegistry.create());
}

inline void EnTTEcs::DestroyAllImpl() { mRegistry.clear(); }

inline void EnTTEcs::DestroyImpl(util::Entity entity) {
  auto e = static_cast<entt::entity>(entity);

  if (mRegistry.valid(e))
    mRegistry.destroy(e);
}

template <typename Component, typename... Args>
inline void EnTTEcs::AddImpl(util::Entity entity, Args &&...args) {
  mRegistry.emplace<Component>(static_cast<entt::entity>(entity),
                               std::forward<Args>(args)...);
}

template <typename Component>
const Component *const EnTTEcs::GetImpl(util::Entity entity) const {
  if (mRegistry.valid(static_cast<entt::entity>(entity)))
    return &mRegistry.get<Component>(static_cast<entt::entity>(entity));
  return nullptr;
}
template <typename... Components> auto EnTTEcs::GetImpl(util::Entity entity) {

  if (!mRegistry.valid(static_cast<entt::entity>(entity)))
    return std::optional<std::tuple<Components &...>>{};

  return std::optional{
      mRegistry.get<Components...>(static_cast<entt::entity>(entity))};
}

template <typename... Components, typename Lambda>
inline void EnTTEcs::EachImpl(Lambda &&lambda) {
  auto view = mRegistry.view<Components...>();

  for (auto entity : view) {
    lambda(static_cast<util::Entity>(entity),
           view.template get<Components>(entity)...);
  }
}

template <typename... Components, typename Lambda>
inline void EnTTEcs::EachImpl(Lambda &&lambda) const {
  const auto view = mRegistry.view<Components...>();
  view.each([&](const auto entity, const Components &...comps) {
    lambda(static_cast<util::Entity>(entity), comps...);
  });
}

}; // namespace ecs
