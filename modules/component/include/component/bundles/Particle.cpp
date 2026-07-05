#include "component/bundles/Particle.hpp"
#include "component/Lifetime.hpp"
#include "component/Position.hpp"
#include "component/Velocity.hpp"
#include "component/shape/Circle.hpp"
#include <chrono>
#include <random>

namespace {
static std::mt19937::result_type seed = static_cast<std::mt19937::result_type>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());
static std::mt19937 gen(seed);
} // namespace

void component::Particle::PositionUpdate(ecs::Impl &buffer,
                                         component::Position &position,
                                         component::Velocity &velocity,
                                         float deltaTime) {
  position.x += velocity.dX * deltaTime;
  position.y += velocity.dY * deltaTime;
}

void component::Particle::VelocityUpdate(ecs::Impl &buffer,
                                         component::Velocity &velocity,
                                         float deltaTime) {
  float speed =
      std::sqrt(velocity.dX * velocity.dX + velocity.dY * velocity.dY);

  if (speed <= component::Particle::MIN_SPEED)
    return;

  // ensure speed stays the same regardless of velocity direction
  float newSpeed = speed * component::Particle::DAMPING;

  // velocity dampening
  float scale = newSpeed / speed;
  velocity.dX *= scale;
  velocity.dY *= scale;
}

void component::Particle::ShapwUpdate(ecs::Impl &buffer,
                                      component::shape::Circle &circle,
                                      float deltaTime) {
  // shift color every 4th frames
  static int32_t counter{};
  if (circle.color < component::Particle::CIRCLE_COLOR_END || counter++ < 3)
    return;
  circle.color -= component::Particle::CIRCLE_COLOR_STEP;
  counter = 0;
}

bool component::Particle::LifeTimeUpdate(ecs::Impl &buffer,
                                         component::Lifetime &lifeTime,
                                         float deltaTime) {
  using ms = std::chrono::milliseconds;
  lifeTime.lifeTime -= std::chrono::duration_cast<std::chrono::milliseconds>(
      std::chrono::duration<float>(deltaTime));
  if (lifeTime.lifeTime > ms(1))
    return true;
  return false;
}

void component::Particle::Create(ecs::Impl &buffer,
                                 const component::Position &position,
                                 const component::Velocity *const velocity,
                                 const component::shape::Circle &circle) {
  using namespace std::chrono_literals;
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Particle>(entity);
  buffer.Add<component::Position>(entity, position);
  buffer.Add<component::shape::Circle>(entity, circle);
  buffer.Add<component::Lifetime>(entity, 4000ms);

  if (velocity)
    buffer.Add<component::Velocity>(entity, *velocity);
  else {
    constexpr float SPEED = 300.0f;
    static std::uniform_real_distribution<float> angleDist(
        0.0f, 2.0f * std::numbers::pi_v<float>);

    float angle = angleDist(gen);

    buffer.Add<component::Velocity>(
        entity,
        component::Velocity{std::cos(angle) * SPEED, std::sin(angle) * SPEED});
  }
}
