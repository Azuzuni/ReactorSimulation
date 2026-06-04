#pragma once

#include "component/Position.hpp"
#include "component/Velocity.hpp"
#include "component/shape/Circle.hpp"
#include "ecs/EcsImpl.hpp"
namespace component {

enum Type { BUTTON, PARTICLE };

class Factory {
  Factory() = delete;
  Factory(Factory &&) = delete;
  Factory(const Factory &) = delete;
  Factory &operator=(Factory &&) = delete;
  Factory &operator=(const Factory &) = delete;
  ~Factory() = delete;

public:
  static void InsertButton(ecs::Impl &buffer);
  static void InsertParticle(ecs::Impl &buffer,
                             const component::Position &position,
                             const component::Velocity &velocity,
                             const component::shape::Circle &circle);
};

} // namespace component
