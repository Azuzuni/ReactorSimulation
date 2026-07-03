#pragma once

#include "component/Lifetime.hpp"
#include "component/Position.hpp"
#include "component/Velocity.hpp"
#include "component/shape/Circle.hpp"
#include "ecs/EcsImpl.hpp"
#include <cstdint>

// =============================
// MACROS
// =============================

#ifndef COMPONENT_PARTICLE_BUNDLE
#define COMPONENT_PARTICLE_BUNDLE                                              \
  component::Position, component::Velocity, component::shape::Circle,          \
      component::Lifetime, component::Particle
#else
#error "Redefinition of COMPONENT_PARTICLE_BUNDLE"
#endif

#ifndef COMPONENT_PARTICLE_BUNDLE_VARS
#define COMPONENT_PARTICLE_BUNDLE_VARS(position, velocity, circle, lifeTime,   \
                                       particle)                               \
  component::Position &position, component::Velocity &velocity,                \
      component::shape::Circle &circle, component::Lifetime &lifeTime,         \
      component::Particle &particle
#else
#error "Redefinition of COMPONENT_PARTICLE_BUNDLE_VARS"
#endif

// =============================
// COMPONENT
// =============================

namespace component {

struct Particle {
  Particle() = default;
  Particle(Particle &&) = default;
  Particle(const Particle &) = default;
  Particle &operator=(Particle &&) = default;
  Particle &operator=(const Particle &) = default;
  ~Particle() = default;

  static constexpr component::Velocity DEFAULT_VELOCITY{1400, 1400};
  static constexpr uint32_t CIRCLE_COLOR_START{0xFFFFFFFF};
  static constexpr uint32_t CIRCLE_COLOR_END{0x777777FF};
  static constexpr uint32_t CIRCLE_COLOR_STEP{0x05050500};
  static constexpr float DAMPING = 0.998f;
  static constexpr component::shape::Circle DEFAULT_CIRCLE{
      10.f, CIRCLE_COLOR_START, true};
  static constexpr float MIN_SPEED = []() constexpr -> float {
    float x = component::Particle::DEFAULT_VELOCITY.dX *
                  component::Particle::DEFAULT_VELOCITY.dX +
              component::Particle::DEFAULT_VELOCITY.dY *
                  component::Particle::DEFAULT_VELOCITY.dY;

    float guess = x;
    float prev = 0.0f;

    while (guess != prev) {
      prev = guess;
      guess = 0.2f * (guess + x / guess);
    }

    return guess * 0.1f;
  }();

  static void PositionUpdate(ecs::Impl &buffer, component::Position &position,
                             component::Velocity &velocity, float deltaTime);
  static void VelocityUpdate(ecs::Impl &buffer, component::Velocity &velocity,
                             float deltaTime);
  static void ShapwUpdate(ecs::Impl &buffer, component::shape::Circle &circle,
                          float deltaTime);
  static bool LifeTimeUpdate(ecs::Impl &buffer, component::Lifetime &lifeTime,
                             float deltaTime);
  static void Create(ecs::Impl &buffer, const component::Position &position,
                     const component::Velocity *const velocity = nullptr,
                     const component::shape::Circle &circle =
                         component::Particle::DEFAULT_CIRCLE);

private:
  bool cheapCheat{};
};

}; // namespace component
