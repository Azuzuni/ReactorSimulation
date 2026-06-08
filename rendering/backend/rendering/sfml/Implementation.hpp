#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "ecs/EcsImpl.hpp"
#include "rendering/RenderIF.hpp"

/**
 * @file
 * @brief SFML rendering CRTP implementation
 *
 * @class SfmlRender
 * @brief CRTP implementation of SFML backend
 *
 * All implementations are called through methods
 * inside the base class.
 */
class SfmlRender : public RenderIF<SfmlRender> {
  friend class RenderIF<SfmlRender>;

private:
  sf::RenderWindow window;

  SfmlRender() = default;

  SfmlRender(const SfmlRender &) = delete;
  SfmlRender &operator=(const SfmlRender &) = delete;

  int GetWidthOfWindowImpl() const noexcept;
  int GetHeightOfWindowImpl() const noexcept;
  bool ShouldCloseImpl() const noexcept;

  sf::Color ToColor(const uint32_t &rgba) const noexcept;

  void ParticleUpdate(const ecs::Impl &buffer) noexcept;
  void ButtonUpdate(const ecs::Impl &buffer) const noexcept;

  void UpdateImpl(const ecs::Impl &buffer) noexcept;

public:
  SfmlRender(int width, int height, const char *title);

  SfmlRender(SfmlRender &&) = default;
  SfmlRender &operator=(SfmlRender &&) = default;

  ~SfmlRender();
};
