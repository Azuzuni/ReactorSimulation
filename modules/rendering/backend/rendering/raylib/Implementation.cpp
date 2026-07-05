#include "rendering/raylib/Implementation.hpp"
#include "component/Position.hpp"
#include "component/shape/Circle.hpp"
#include "component/shape/Rectangle.hpp"
#include "core/Color.hpp"
#include "ecs/EcsImpl.hpp"
#include "raylib.h"
#include "utils/Configuration.hpp"
#include "utils/InputData.hpp"
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

constexpr Color RaylibRender::ToColor(const color::Color &rgba) const noexcept {
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

void RaylibRender::DrawRectangle(const ecs::Impl &buffer) const noexcept {
  buffer.Each<component::Position, component::shape::Rectangle>(
      [&](const util::Entity, const component::Position &position,
          const component::shape::Rectangle &rectangle) -> bool {
        ::DrawRectangle(position.x, position.y, rectangle.width,
                        rectangle.height, ToColor(rectangle.color));
        return true;
      });
}

InputData RaylibRender::InputHandler() const noexcept {
  InputData input{};
  if (IsKeyDown(KEY_DOWN))
    input.key = KeyId::ARROW_DOWN;

  if (IsKeyDown(KEY_UP))
    input.key = KeyId::ARROW_UP;

  return input;
}

InputData RaylibRender::UpdateImpl(const ecs::Impl &buffer) const noexcept {
  ::BeginDrawing();
  ::ClearBackground(ToColor(color::BACKGROUND));
  this->DrawCircle(buffer);
  this->DrawRectangle(buffer);

  ::EndDrawing();
  return this->InputHandler();
}
