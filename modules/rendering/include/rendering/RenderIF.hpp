#pragma once
#include "ecs/EcsImpl.hpp"
#include "utils/InputData.hpp"

// ===================================================
// 1. Declarations
// ===================================================

//! @brief Rendering interface (CRTP)
//!
//! @tparam Impl selected child class containing implementations
template <typename Impl> class RenderIF {
protected:
  //! @brief derived() is used to call children methods through parent (CRTP)
  constexpr inline Impl &derived() { return static_cast<Impl &>(*this); }
  constexpr const inline Impl &derived() const {
    return static_cast<const Impl &>(*this);
  }

  //-----------------------------------
  // Constructors
  //-----------------------------------
  RenderIF() = default;
  RenderIF(const RenderIF &) = delete;
  RenderIF &operator=(const RenderIF &) = delete;
  RenderIF(RenderIF &&) = default;
  RenderIF &operator=(RenderIF &&) = default;
  ~RenderIF() = default;

public:
  //-----------------------------------
  // Methods
  //-----------------------------------

  //! @brief returns window width
  //! @return int
  [[nodiscard]] int GetWidthOfWindow() const noexcept;

  //! @brief returns window height
  //! @return int
  [[nodiscard]] int GetHeightOfWindow() const noexcept;

  //! @brief returns true when window should close
  //! @return bool
  [[nodiscard]] bool ShouldClose() const noexcept;

  //! @brief method that works as entry point for all render elements
  //!
  //! @param buffer ecs buffer containing elements to render
  [[nodiscard]] InputData Update(const ecs::Impl &buffer) const noexcept;

  //! @brief method that works as entry point for all render elements
  //!
  //! this version is non const for member variables to keep compatibility
  //! with some backends such as sfml
  //!
  //! @param buffer ecs buffer containing elements to render
  [[nodiscard]] InputData Update(const ecs::Impl &buffer) noexcept;
};

// ===================================================
// 2. Implementations
// ===================================================

// GetWidthOfWindow
template <typename Impl>
inline int RenderIF<Impl>::GetWidthOfWindow() const noexcept {
  return derived().GetWidthOfWindowImpl();
}

// GetHeightOfWindow
template <typename Impl>
inline int RenderIF<Impl>::GetHeightOfWindow() const noexcept {
  return derived().GetHeightOfWindowImpl();
}

// ShouldClose
template <typename Impl>
[[nodiscard]] inline bool RenderIF<Impl>::ShouldClose() const noexcept {
  return derived().ShouldCloseImpl();
}

// Update (const noexcept)
template <typename Impl>
inline InputData
RenderIF<Impl>::Update(const ecs::Impl &buffer) const noexcept {
  return derived().UpdateImpl(buffer);
}

// Update (noexcept)
template <typename Impl>
inline InputData RenderIF<Impl>::Update(const ecs::Impl &buffer) noexcept {
  return derived().UpdateImpl(buffer);
}
