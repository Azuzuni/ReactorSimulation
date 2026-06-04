#include "component/factory/Factory.hpp"
#include "component/Lifetime.hpp"
#include "component/Position.hpp"
#include "component/Types.hpp"
#include "component/Velocity.hpp"
#include "component/shape/Circle.hpp"
#include "component/shape/Rectangle.hpp"
#include "core/Color.hpp"
#include "utils/Configuration.hpp"
using namespace component;

void Factory::InsertButton(ecs::Impl &buffer) {
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Button>(entity);
  buffer.Add<component::Position>(entity, component::Position{750, 400});
  buffer.Add<component::shape::Rectangle>(
      entity, component::shape::Rectangle{200, 100, color::BUTTON});
}

void Factory::InsertParticle(ecs::Impl &buffer,
                             const component::Position &position,
                             const component::Velocity &velocity,
                             const component::shape::Circle &circle) {
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Particle>(entity);
  buffer.Add<component::Position>(entity, position);
  buffer.Add<component::Velocity>(entity, velocity);
  buffer.Add<component::shape::Circle>(entity, circle);
  buffer.Add<component::Lifetime>(entity, 1.f);
}
