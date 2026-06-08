#include "rendering/raylib/Implementation.hpp"
#include "component/Position.hpp"
#include "component/shape/Circle.hpp"
#include "core/Color.hpp"
#include "ecs/EcsImpl.hpp"
#include "raylib.h"
#include "utils/Configuration.hpp"
#include <cstdint>

// ===================================================
// 1. Constructor / Destructor
// ===================================================

RaylibRender::RaylibRender(int width, int height, const char *title) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED);
  InitWindow(width, height, title);
  SetTargetFPS(60);
}

RaylibRender::~RaylibRender() { CloseWindow(); }

// ===================================================
// 2. Implementations
// ===================================================

int RaylibRender::GetWidthOfWindowImpl() const noexcept {
  return GetScreenWidth();
}
int RaylibRender::GetHeightOfWindowImpl() const noexcept {
  return GetScreenHeight();
}

bool RaylibRender::ShouldCloseImpl() const noexcept {
  return WindowShouldClose();
}
// ---------------------------------------------------

constexpr Color RaylibRender::ToColor(const uint32_t &rgba) const noexcept {
  return Color(static_cast<uint8_t>((rgba >> 24) & 0xFF),
               static_cast<uint8_t>((rgba >> 16) & 0xFF),
               static_cast<uint8_t>((rgba >> 8) & 0xFF),
               static_cast<uint8_t>((rgba) & 0xFF));
}

void RaylibRender::DrawCircle(const ecs::Impl &buffer) const noexcept {
  buffer.Each<component::Position, component::shape::Circle>(
      [&](const util::Entity, const component::Position &position,
          const component::shape::Circle &circle) -> bool {
        ::DrawCircle(static_cast<int>(position.x), static_cast<int>(position.y),
                     circle.radius, ToColor(circle.color));
        return true;
      });
}

void RaylibRender::UpdateImpl(const ecs::Impl &buffer) const noexcept {
  ::BeginDrawing();
  ::ClearBackground(ToColor(color::BACKGROUND));
  this->DrawCircle(buffer);

  ::EndDrawing();
}
