#include "component/bundles/Fuel.hpp"
#include "component/Position.hpp"
#include <chrono>
#include <random>
#include <vector>

namespace {
static std::mt19937::result_type seed = static_cast<std::mt19937::result_type>(
    std::chrono::high_resolution_clock::now().time_since_epoch().count());
static std::mt19937 gen(seed);
} // namespace
void component::Fuel::Create(ecs::Impl &buffer,
                             const component::Position &position,
                             const component::shape::Circle &circle) {
  util::Entity entity{buffer.Create()};
  buffer.Add<component::Fuel>(entity);
  buffer.Add<component::Position>(entity, position);
  buffer.Add<component::shape::Circle>(entity, circle);
  buffer.Add<component::Decay>(entity);
}

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
