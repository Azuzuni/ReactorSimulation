#pragma once
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"

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
   * @brief Wrapper for DeltaTime
   * @return float
   */
  [[nodiscard]] inline float GetDeltaTime() const noexcept {
    return derived().GetDeltaTimeImpl();
  }

  /**
   * @brief Wrapper for renderer implementation of
   * whether window should close or not
   * @return bool
   */
  [[nodiscard]] inline bool ShouldClose() const noexcept {
    return derived().ShouldCloseImpl();
  }

  /**
   * @brief Begin Drawing Frame
   */
  inline void StartFrame() const { derived().StartFrameImpl(); }

  /**
   * @brief End Drawing Frame
   */
  inline void EndFrame() const { derived().EndFrameImpl(); }

  /**
   * @brief Fill background color from backend implementation
   *
   * @param color -> util::Color r g b a value
   */
  inline void Clear(const util::Color &color) const noexcept {
    derived().ClearImpl(color);
  }

  /**
   * @brief Draw circle from backend implementation
   *
   * @param x PosType x -> X position coordinate
   * @param y PosType y -> Y position coordinate
   * @param r float r -> circle radius
   * @param color -> util::Color r g b a.
   */
  inline void Circle(util::PosType x, util::PosType y, float r,
                     const util::Color &color) const {
    derived().CircleImpl(x, y, r, color);
  }

  /**
   * @brief Draw square from backend implementation
   *
   * @param x PosType -> X position coordinate
   * @param y PosType -> Y position coordinate
   * @param width PosType -> width of the rect
   * @param height PosType -> height of the rect
   * @param color [TODO:parameter]
   */
  inline void Rect(util::PosType x, util::PosType y, util::PosType width,
                   util::PosType height,
                   const util::Color &color) const noexcept {
    derived().RectImpl(x, y, width, height, color);
  }
};
