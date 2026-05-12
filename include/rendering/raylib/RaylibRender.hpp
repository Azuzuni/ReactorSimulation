#pragma once
#include "rendering/RenderIF.hpp"
#include "utils/Configuration.hpp"
#include "utils/Color.hpp"
/**
 * @file
 * @brief raylib rendering CRTP implementation
 *
 * @class RaylibRender
 * @brief CRTP implementation of raylib backend
 * all implementations are called through methods
 * inside the base class
 */
class RaylibRender : public RenderIF<RaylibRender> {
  friend class RenderIF<RaylibRender>;
  RaylibRender() = default;
  RaylibRender(const RaylibRender &) = delete;
  RaylibRender &operator=(const RaylibRender &) = delete;

  int GetWidthOfWindowImpl() const noexcept;
  int GetHeightOfWindowImpl() const noexcept;
  float GetDeltaTimeImpl() const noexcept;

  bool ShouldCloseImpl() const noexcept;
  void StartFrameImpl() const noexcept;
  void EndFrameImpl() const noexcept;

  void ClearImpl(const util::Color &) const noexcept;
  void CircleImpl(util::PosType, util::PosType, float,
                  const util::Color &) const noexcept;
  void RectImpl(util::PosType x, util::PosType y, util::PosType width,
                util::PosType height, const util::Color &color) const noexcept;

public:
  RaylibRender(int, int, const char *);
  RaylibRender(RaylibRender &&) = default;
  RaylibRender &operator=(RaylibRender &&) = default;
  ~RaylibRender();
};
