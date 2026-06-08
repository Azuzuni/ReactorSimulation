#include "rendering/sfml/Implementation.hpp"
#include "component/Position.hpp"
#include "component/shape/Circle.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cstdint>

// ===================================================
// Constructor / Destructor
// ===================================================

SfmlRender::SfmlRender(int width, int height, const char *title)
    : window(sf::VideoMode({static_cast<unsigned int>(width),
                            static_cast<unsigned int>(height)}),
             title) {

  window.setFramerateLimit(60);

  window.setSize(sf::Vector2u(static_cast<unsigned int>(width),
                              static_cast<unsigned int>(height)));

  window.setPosition(sf::Vector2i(0, 0));
}

SfmlRender::~SfmlRender() = default;

// ===================================================
// Implementations
// ===================================================

int SfmlRender::GetWidthOfWindowImpl() const noexcept {
  return static_cast<int>(window.getSize().x);
}

int SfmlRender::GetHeightOfWindowImpl() const noexcept {
  return static_cast<int>(window.getSize().y);
}

bool SfmlRender::ShouldCloseImpl() const noexcept { return !window.isOpen(); }

// ---------------------------------------------------

sf::Color SfmlRender::ToColor(const uint32_t &rgba) const noexcept {
  return sf::Color(static_cast<uint8_t>((rgba >> 24) & 0xFF),
                   static_cast<uint8_t>((rgba >> 16) & 0xFF),
                   static_cast<uint8_t>((rgba >> 8) & 0xFF),
                   static_cast<uint8_t>(rgba & 0xFF));
}

void SfmlRender::ParticleUpdate(const ecs::Impl &buffer) noexcept {

  buffer.Each<component::Position, component::shape::Circle>(
      [&](const util::Entity, const component::Position &position,
          const component::shape::Circle &circle) -> bool {
        sf::CircleShape shape(circle.radius);
        shape.setFillColor(ToColor(circle.color));

        shape.setPosition(sf::Vector2f(position.x - circle.radius,
                                       position.y - circle.radius));

        window.draw(shape);
        return true;
      });
}

void SfmlRender::UpdateImpl(const ecs::Impl &buffer) noexcept {

  while (auto event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }

  window.clear(ToColor(color::BACKGROUND));

  ParticleUpdate(buffer);

  window.display();
}
