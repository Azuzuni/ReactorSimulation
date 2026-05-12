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

  template<typename... Args>
  util::Entity CreateImpl(Args&&...);

  template <typename Component, typename... Args>
  Component & AddImpl(util::Entity entity, Args &&...args);

  template <typename... Components, typename Lambda> void EachImpl(Lambda &&lambda);

public:
  EnTTEcs() = default;
  EnTTEcs(EnTTEcs &&) = default;
  EnTTEcs &operator=(EnTTEcs &&) = default;
  ~EnTTEcs() = default;
};

}; // namespace ecs


#include "ecs/entt/EnTTEcs.inl"

