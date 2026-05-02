#pragma once
#include "rendering/RendererIF.hpp"
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
class RaylibRender : public RendererIF<RaylibRender> {
  friend RendererIF<RaylibRender>;
  RaylibRender() = default;
  RaylibRender(const RaylibRender &) = delete;
  RaylibRender &operator=(const RaylibRender &) = delete;

  int GetWidthOfWindowImpl() const noexcept;
  int GetHeightOfWindowImpl() const noexcept;
  float GetDeltaTimeImpl() const noexcept;

  bool ShouldCloseImpl() const noexcept;
  void StartFrameImpl() const noexcept;
  void EndFrameImpl() const noexcept;

  void ClearImpl(const cnf::Color &) const noexcept;
  void CircleImpl(cnf::PosType, cnf::PosType, float,
                  const cnf::Color &) const noexcept;
  void RectImpl(cnf::PosType x, cnf::PosType y, cnf::PosType width,
                cnf::PosType height, const cnf::Color &color) const noexcept;

public:
  RaylibRender(int, int, const char *);
  RaylibRender(RaylibRender &&) = default;
  RaylibRender &operator=(RaylibRender &&) = default;
  ~RaylibRender();
};
