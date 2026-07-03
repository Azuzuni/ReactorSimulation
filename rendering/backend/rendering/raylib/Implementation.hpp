#pragma once
#include "ecs/EcsImpl.hpp"
#include "raylib.h"
#include "rendering/RenderIF.hpp"
#include "utils/InputData.hpp"
#include <cstdint>
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
  bool ShouldCloseImpl() const noexcept;

  constexpr Color ToColor(const uint32_t &rgba) const noexcept;
  void DrawCircle(const ecs::Impl &buffer) const noexcept;
  void DrawRectangle(const ecs::Impl &buffer) const noexcept;
  InputData InputHandler() const noexcept;
  InputData UpdateImpl(const ecs::Impl &buffer) const noexcept;

public:
  RaylibRender(int, int, const char *);
  RaylibRender(RaylibRender &&) = default;
  RaylibRender &operator=(RaylibRender &&) = default;
  ~RaylibRender();
};
