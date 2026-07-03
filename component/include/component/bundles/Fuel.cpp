#include "component/bundles/Fuel.hpp"
#include "component/Position.hpp"
#include "component/bundles/Particle.hpp"
#include "utils/Configuration.hpp"
#include <chrono>
#include <random>

namespace {
static std::mt19937::result_type seed = static_cast<std::mt19937::result_type>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());
static std::mt19937 gen(seed);
} // namespace

component::Position component::Fuel::DecayUpdate(ecs::Impl &buffer,
                                                 component::Position &position,
                                                 component::Decay &decay,
                                                 float deltaTime) {
  using ms = std::chrono::milliseconds;
  static std::uniform_real_distribution<float> range(1, 5);
  static std::uniform_real_distribution<float> spawnRate{0, 1};
  component::Position result{-1, -1};
  if (decay.lifeTime <= ms(1)) {
    if (spawnRate(gen) < 0.05f)
      result = position;
    decay.lifeTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::duration<float>(range(gen)));
  } else
    decay.lifeTime -= std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::duration<float>(deltaTime));
  return result;
}

bool component::Fuel::CollisionCheck(ecs::Impl &buffer,
                                     component::Position &position,
                                     component::shape::Circle &circle) {
  if (circle.trigger)
    return false;
  bool result{};

  // _p suffix for _PARTICLE
  buffer.Each<COMPONENT_PARTICLE_BUNDLE>(
      [&](util::Entity entity,
          COMPONENT_PARTICLE_BUNDLE_VARS(position_p, velocity_p, circle_p,
                                         lifeTime_p, particle_p)) -> bool {
        if (circle_p.color != component::Particle::CIRCLE_COLOR_END)
          return true;

        util::PosType dX{std::abs(position.x - position_p.x)};
        util::PosType dY{std::abs(position.y - position_p.y)};
        float radiusSum{circle.radius + circle_p.radius};
        result =
            static_cast<float>(dX * dX + dY * dY) <= (radiusSum * radiusSum);
        if (result)
          buffer.Destroy(entity);
        return !result;
      });
  return result;
}

void component::Fuel::Create(ecs::Impl &buffer,
                             const component::Position &position,
                             const component::shape::Circle &circle) {
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Fuel>(entity);
  buffer.Add<component::Position>(entity, position);
  buffer.Add<component::shape::Circle>(entity, circle);
  buffer.Add<component::Decay>(entity);
}
