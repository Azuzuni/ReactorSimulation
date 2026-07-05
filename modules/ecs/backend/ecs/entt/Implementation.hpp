#pragma once
#include "ecs/EcsIF.hpp"
#include "entt/entity/fwd.hpp"
#include "entt/entt.hpp"
#include "utils/Configuration.hpp"
namespace ecs {

// ===================================================
// 1. Declarations
// ===================================================

//! @brief entt implementation of EcsIF
class EnTTEcs : public EcsIF<EnTTEcs> {
  //! friend access allows parent to call Impl methods
  friend class EcsIF<EnTTEcs>;

  //-----------------------------------
  // Private Constructors
  //-----------------------------------
  EnTTEcs(const EnTTEcs &) = delete;
  EnTTEcs &operator=(const EnTTEcs &) = delete;

  //-----------------------------------
  // Member Variables
  //-----------------------------------
  entt::registry mRegistry;

  //-----------------------------------
  // Member Methods
  //-----------------------------------

  //! @brief implementation of Create()
  //! @see ecs::EcsIF
  util::Entity CreateImpl();

  //! @brief implementation of DestroyAll()
  //! @see ecs::EcsIF
  void DestroyAllImpl();

  //! @brief implementation of Destroy()
  //! @see ecs::EcsIF
  void DestroyImpl(util::Entity entity);

  //! @brief implementation of Add()
  //! @see ecs::EcsIF
  template <typename Component, typename... Args>
  void AddImpl(util::Entity entity, Args &&...args);

  //! @brief implementation of Get() (const)
  //! @see ecs::EcsIF
  template <typename Component> const Component *GetImpl(util::Entity) const;

  //! @brief implementation of Get()
  //! @see ecs::EcsIF
  template <typename... Components> auto GetImpl(util::Entity);

  //! @brief implementation of Each() (const)
  //! @see ecs::EcsIF
  template <typename... components, typename lambda>
  void EachImpl(lambda &&function) const;

  //! @brief implementation of Each()
  //! @see ecs::EcsIF
  template <typename... Components, typename Lambda>
  void EachImpl(Lambda &&function);

public:
  //-----------------------------------
  // Public Constructors
  //-----------------------------------
  EnTTEcs() = default;
  EnTTEcs(EnTTEcs &&) = default;
  EnTTEcs &operator=(EnTTEcs &&) = default;
  ~EnTTEcs() = default;
};

}; // namespace ecs

// ===================================================
// 2. Implementations
// ===================================================

// CreateImpl
inline util::Entity ecs::EnTTEcs::CreateImpl() {
  return static_cast<util::Entity>(mRegistry.create());
}

// DestroyAllImpl
inline void ecs::EnTTEcs::DestroyAllImpl() { mRegistry.clear(); }

// DestroyImpl
inline void ecs::EnTTEcs::DestroyImpl(util::Entity entity) {
  auto e = static_cast<entt::entity>(entity);

  if (mRegistry.valid(e))
    mRegistry.destroy(e);
}

// AddImpl
template <typename Component, typename... Args>
inline void ecs::EnTTEcs::AddImpl(util::Entity entity, Args &&...args) {
  mRegistry.emplace<Component>(static_cast<entt::entity>(entity),
                               std::forward<Args>(args)...);
}

// GetImpl (const)
template <typename Component>
const Component *ecs::EnTTEcs::GetImpl(util::Entity entity) const {
  if (mRegistry.valid(static_cast<entt::entity>(entity)))
    return &mRegistry.get<Component>(static_cast<entt::entity>(entity));
  return nullptr;
}

// GetImpl
template <typename... Components>
auto ecs::EnTTEcs::GetImpl(util::Entity entity) {

  if (!mRegistry.valid(static_cast<entt::entity>(entity)))
    return std::optional<std::tuple<Components &...>>{};

  return std::optional{
      mRegistry.get<Components...>(static_cast<entt::entity>(entity))};
}

// EachImpl (const)
template <typename... Components, typename Lambda>
inline void ecs::EnTTEcs::EachImpl(Lambda &&function) const {
  const auto view = mRegistry.view<Components...>();
  for (const auto &entity : view) {
    if (!function(static_cast<util::Entity>(entity),
                  view.template get<Components>(entity)...))
      break;
  }
}

// EachImpl
template <typename... Components, typename Lambda>
inline void ecs::EnTTEcs::EachImpl(Lambda &&function) {
  auto view = mRegistry.view<Components...>();
  for (auto &entity : view) {
    if (!function(static_cast<util::Entity>(entity),
                  view.template get<Components>(entity)...))
      break;
  }
}
