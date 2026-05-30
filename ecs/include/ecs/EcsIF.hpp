#pragma once

#include "utils/Configuration.h"
#include <utility>
namespace ecs {

template <typename Impl> class EcsIF {
protected:
  EcsIF() = default;
  ~EcsIF() = default;
  constexpr inline Impl &derived() { return static_cast<Impl &>(*this); }
  constexpr const inline Impl &derived() const {
    return static_cast<const Impl &>(*this);
  }

public:
  EcsIF(EcsIF &&) = default;
  EcsIF(const EcsIF &) = default;
  EcsIF &operator=(EcsIF &&) = default;
  EcsIF &operator=(const EcsIF &) = default;
  [[nodiscard]] util::Entity Create() noexcept {
    return derived().CreateImpl();
  }

  void DestroyAll() noexcept { derived().DestroyAllImpl(); }

  void Destroy(util::Entity entity) noexcept { derived().DestroyImpl(entity); }

  template <typename Component, typename... Args>
  void Add(util::Entity entity, Args &&...args) noexcept {
    derived().template AddImpl<Component>(entity, std::forward<Args>(args)...);
  }

  template <typename Component>
  [[nodiscard]] const Component *const Get(util::Entity entity) const noexcept {
    return derived().template GetImpl<Component>(
        std::forward<util::Entity>(entity));
  }
  
  template <typename... Components>
  [[nodiscard]] auto Get(util::Entity entity) noexcept {
    return derived().template GetImpl<Components...>(
        std::forward<util::Entity>(entity));
  }

  template <typename... Components, typename Lambda>
  void Each(Lambda &&lambda) noexcept {
    derived().template EachImpl<Components...>(std::forward<Lambda>(lambda));
  }

  template <typename... Components, typename Lambda>
  void Each(Lambda &&lambda) const noexcept {
    derived().template EachImpl<Components...>(std::forward<Lambda>(lambda));
  }
};

}; // namespace ecs
