#include "ecs/System.hpp"
#include "component/Lifetime.hpp"
#include "component/Position.hpp"
#include "component/bundles/Fuel.hpp"
#include "component/bundles/Particle.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include <chrono>
#include <iostream>
#include <vector>

void ecs::System::Flush(ecs::Impl &backBuffer) {
  std::vector<util::Entity> destroy{};
  backBuffer.Each<component::Lifetime>(
      [&](util::Entity entity, component::Lifetime &lifeTime) -> bool {
        using namespace std::chrono_literals;
        if (lifeTime.lifeTime <= 0ms)
          destroy.emplace_back(entity);
        return true;
      });

  for (auto &id : destroy)
    backBuffer.Destroy(id);
}

void ecs::System::ParticleUpdate(ecs::Impl &buffer, float deltaTime) {
  using ms = std::chrono::milliseconds;

  buffer.Each<COMPONENT_PARTICLE_BUNDLE>([&](util::Entity entity,
                                             COMPONENT_PARTICLE_BUNDLE_VARS(
                                                 position, velocity, circle,
                                                 lifeTime, particle)) -> bool {
    if (!component::Particle::LifeTimeUpdate(buffer, lifeTime, deltaTime))
      return true;

    component::Particle::PositionUpdate(buffer, position, velocity, deltaTime);
    component::Particle::VelocityUpdate(buffer, velocity, deltaTime);
    component::Particle::ShapwUpdate(buffer, circle, deltaTime);
    return true;
  });
}

void ecs::System::FuelUpdate(ecs::Impl &buffer, float deltaTime) {
  std::vector<component::Position> particleQueue{};

  buffer.Each<COMPONENT_FUEL_BUNDLE>(
      [&](util::Entity entity, COMPONENT_FUEL_BUNDLE_VARS(
                                   position, decay, circle, fuelTag)) -> bool {
        auto result{
            component::Fuel::DecayUpdate(buffer, position, decay, deltaTime)};
        if (result.x != -1 && result.y != -1)
          particleQueue.emplace_back(result);
        if (component::Fuel::CollisionCheck(buffer, position, circle)) {
          circle.trigger = true;
          circle.color = 0x2222AAFF;
          particleQueue.emplace_back(position);
          particleQueue.emplace_back(position);
          particleQueue.emplace_back(position);
        }
        return true;
      });

  // spawn Particles
  for (const auto &position : particleQueue)
    component::Particle::Create(buffer, position);
}

void ecs::System::Update(ecs::Impl &buffer, float deltaTime) {
  ParticleUpdate(buffer, deltaTime);
  FuelUpdate(buffer, deltaTime);
  Flush(buffer);
}
