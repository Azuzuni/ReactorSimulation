#pragma once
#include "core/Color.h"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include <utility>

/**
 * @file
 * @brief CRTP interface for rendering
 *
 * @class RenderIF
 * @brief CRTP base class for rendering
 * This is sort of Interface / Wrapper
 *
 * usage of child classes is supposed
 * to be used through methods calls of base class
  @tparam Impl CRTP child class with implementations
 */
template <typename Impl> class RenderIF {
protected:
  RenderIF() = default;
  RenderIF(const RenderIF &) = delete;
  RenderIF &operator=(const RenderIF &) = delete;
  RenderIF(RenderIF &&) = default;
  RenderIF &operator=(RenderIF &&) = default;
  ~RenderIF() = default;
  constexpr inline Impl &derived() { return static_cast<Impl &>(*this); }
  constexpr const inline Impl &derived() const {
    return static_cast<const Impl &>(*this);
  }

public:
  /**
   * @brief Wrapper for window horizontal size
   * @return int
   */
  [[nodiscard]] inline int GetWidthOfWindow() const noexcept {
    return derived().GetWidthOfWindowImpl();
  }

  /**
   * @brief Wrapper for window vertical size
   * @return int
   */
  [[nodiscard]] inline int GetHeightOfWindow() const noexcept {
    return derived().GetHeightOfWindowImpl();
  }

  /**
   * @brief Wrapper for renderer implementation of
   * whether window should close or not
   * @return bool
   */
  [[nodiscard]] inline bool ShouldClose() const noexcept {
    return derived().ShouldCloseImpl();
  }

  inline void Update(const ecs::Impl &buffer) const noexcept {
    derived().UpdateImpl(buffer);
  }
};
