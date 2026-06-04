#include "core/Color.h"
#include "component/Position.h"
#include "component/shape/Circle.h"
#include "component/shape/Rectangle.h"
#include "ecs/EcsImpl.h"
#include "raylib.h"
#include "rendering/raylib/RaylibRender.h"
#include "utils/Configuration.h"
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

constexpr void
RaylibRender::ParticleUpdate(const ecs::Impl &buffer) const noexcept {
  // buffer.Each<component::bundle::Particle>(
  //     [&](const util::Entity, const component::bundle::Particle &particle) {
  //       ::DrawCircle(static_cast<int>(particle.position.x),
  //                    static_cast<int>(particle.position.y),
  //                    particle.circle.radius, ToColor(particle.circle.color));
  //     });

  buffer.Each<component::Position, component::shape::Circle>(
      [&](const util::Entity, const component::Position &position, const component::shape::Circle &circle) {
        ::DrawCircle(static_cast<int>(position.x),
                     static_cast<int>(position.y),
                     circle.radius, ToColor(circle.color));
      });
}

// constexpr void
// RaylibRender::ButtonUpdate(const ecs::Impl &buffer) const noexcept {
//   buffer.Each<component::bundle::Button>(
//       [&](const util::Entity, const component::bundle::Button &button) {
//         ::DrawRectangle(static_cast<int>(button.position.x),
//                         static_cast<int>(button.position.y),
//                         static_cast<int>(button.rectangle.width),
//                         static_cast<int>(button.rectangle.height),
//                         ToColor(button.rectangle.color));
//       });
// }

void RaylibRender::UpdateImpl(const ecs::Impl &buffer) const noexcept {
  ::BeginDrawing();
  ::ClearBackground(ToColor(color::BACKGROUND));
  ParticleUpdate(buffer);

  ::EndDrawing();
}
