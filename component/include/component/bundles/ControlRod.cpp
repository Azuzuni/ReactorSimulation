#include "component/bundles/ControlRod.hpp"
#include "component/Position.hpp"
#include "component/bundles/Particle.hpp"
#include "component/shape/Rectangle.hpp"
#include "utils/InputData.hpp"

bool component::ControlRod::CollisionCheck(
    ecs::Impl &buffer, component::Position &position,
    component::shape::Rectangle &rectangle, float deltaTime) {
  if (rectangle.trigger)
    return false;
  bool result{};

  // AI GENERATED
  auto circleRectCollision = [&](float cx, float cy, float radius, float rx,
                                 float ry, float rw, float rh) -> bool {
    float closestX = std::max(rx, std::min(cx, rx + rw));
    float closestY = std::max(ry, std::min(cy, ry + rh));

    float dx = cx - closestX;
    float dy = cy - closestY;

    return dx * dx + dy * dy <= radius * radius;
  };

  // _p suffix for _PARTICLE
  buffer.Each<COMPONENT_PARTICLE_BUNDLE>(
      [&](util::Entity entity,
          COMPONENT_PARTICLE_BUNDLE_VARS(position_p, velocity_p, circle_p,
                                         lifeTime_p, particle_p)) -> bool {
        result = circleRectCollision(position_p.x, position_p.y,
                                     circle_p.radius, position.x, position.y,
                                     rectangle.width, rectangle.height);
        if (result) {
          circle_p.color = component::Particle::CIRCLE_COLOR_END;
          velocity_p.dX *= -0.5;
          component::Particle::PositionUpdate(buffer, position_p, velocity_p,
                                              deltaTime);
          circle_p.trigger = false;
        }
        return !result;
      });
  return result;
}

void component::ControlRod::Move(ecs::Impl &buffer, InputData &inputData,
                                 KeyId direction, float deltaTime) {
  if (inputData.key == direction) {
    buffer.Each<COMPONENT_CONTROL_ROD_BUNDLE>(
        [&](util::Entity, COMPONENT_CONTROL_ROD_BUNDLE_VARS(
                              position, rectangle, controlRod)) -> bool {
          if (direction == KeyId::ARROW_UP)
            position.y -= 500 * deltaTime;
          else
            position.y += 500 * deltaTime;
          return true;
        });
  }
}

void component::ControlRod::Create(
    ecs::Impl &buffer, const component::Position &position,
    const component::shape::Rectangle &rectangle) {
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Position>(entity, position);
  buffer.Add<component::shape::Rectangle>(entity, rectangle);
  buffer.Add<component::ControlRod>(entity);
}
