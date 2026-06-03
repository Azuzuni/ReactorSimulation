#pragma once
#include "ecs/EcsIF.hpp"
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
  template <typename... Components>
  auto GetImpl(util::Entity);

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

#include "ecs/entt/EnTTEcs.tpp"
