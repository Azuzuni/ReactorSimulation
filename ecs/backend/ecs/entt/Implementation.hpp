#pragma once
#include "ecs/EcsIF.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "utils/Configuration.hpp"
namespace ecs {

class EnTTEcs : public EcsIF<EnTTEcs> {
  friend class EcsIF<EnTTEcs>;
  EnTTEcs(const EnTTEcs &) = delete;
  EnTTEcs &operator=(const EnTTEcs &) = delete;

  // member variables
  entt::registry mRegistry;

  // member methods

  util::Entity CreateImpl();

  void DestroyAllImpl();
  void DestroyImpl(util::Entity entity);

  template <typename Component, typename... Args>
  void AddImpl(util::Entity entity, Args &&...args);

  template <typename Component>
  const Component *const GetImpl(util::Entity) const;
  template <typename... Components> auto GetImpl(util::Entity);

  template <typename... Components, typename Lambda>
  void EachImpl(Lambda &&lambda);
  template <typename... Components, typename Lambda>
  void EachImpl(Lambda &&lambda) const;

public:
  EnTTEcs() = default;
  EnTTEcs(EnTTEcs &&) = default;
  EnTTEcs &operator=(EnTTEcs &&) = default;
  ~EnTTEcs() = default;
};

}; // namespace ecs

inline util::Entity ecs::EnTTEcs::CreateImpl() {
  return static_cast<util::Entity>(mRegistry.create());
}

inline void ecs::EnTTEcs::DestroyAllImpl() { mRegistry.clear(); }

inline void ecs::EnTTEcs::DestroyImpl(util::Entity entity) {
  auto e = static_cast<entt::entity>(entity);

  if (mRegistry.valid(e))
    mRegistry.destroy(e);
}

template <typename Component, typename... Args>
inline void ecs::EnTTEcs::AddImpl(util::Entity entity, Args &&...args) {
  mRegistry.emplace<Component>(static_cast<entt::entity>(entity),
                               std::forward<Args>(args)...);
}

template <typename Component>
const Component *const ecs::EnTTEcs::GetImpl(util::Entity entity) const {
  if (mRegistry.valid(static_cast<entt::entity>(entity)))
    return &mRegistry.get<Component>(static_cast<entt::entity>(entity));
  return nullptr;
}
template <typename... Components>
auto ecs::EnTTEcs::GetImpl(util::Entity entity) {

  if (!mRegistry.valid(static_cast<entt::entity>(entity)))
    return std::optional<std::tuple<Components &...>>{};

  return std::optional{
      mRegistry.get<Components...>(static_cast<entt::entity>(entity))};
}

template <typename... Components, typename Lambda>
inline void ecs::EnTTEcs::EachImpl(Lambda &&lambda) {
  auto view = mRegistry.view<Components...>();
  for (auto &entity : view) {
    if (!lambda(static_cast<util::Entity>(entity),
                view.template get<Components>(entity)...))
      break;
  }
}

template <typename... Components, typename Lambda>
inline void ecs::EnTTEcs::EachImpl(Lambda &&lambda) const {
  const auto view = mRegistry.view<Components...>();
  for (const auto &entity : view) {
    if (!lambda(static_cast<util::Entity>(entity),
                view.template get<Components>(entity)...))
      break;
  }
}; // namespace ecs
