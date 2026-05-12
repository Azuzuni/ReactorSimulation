#pragma once

#include "utils/Configuration.hpp"
#include <utility>
namespace ecs {

template <typename Impl> class EcsIF {
protected:
  EcsIF() = default;
  EcsIF(EcsIF &&) = default;
  EcsIF(const EcsIF &) = default;
  EcsIF &operator=(EcsIF &&) = default;
  EcsIF &operator=(const EcsIF &) = default;
  ~EcsIF() = default;
  constexpr inline Impl &derived() { return static_cast<Impl &>(*this); }
  constexpr const inline Impl &derived() const {
    return static_cast<const Impl &>(*this);
  }

public:
  template <typename... Args>
  [[nodiscard]] util::Entity Create(Args &&...args) const noexcept {
    return derived().CreateImpl(std::forward<Args>(args)...);
  }

  template <typename Component, typename... Args>
  [[nodiscard]] Component &Add(util::Entity entity,
                               Args &&...args) const noexcept {
    return derived().template AddImpl<Component>(entity,
                                                 std::forward<Args>(args)...);
  }

  template <typename... Components, typename Lambda>
  void Each(Lambda &&lambda) const noexcept {
    derived().template EachImpl<Components...>(std::forward<Lambda>(lambda));
  }
};

}; // namespace ecs
