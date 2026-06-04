#include "ecs/System.hpp"
#include "component/Lifetime.hpp"
#include "component/Position.hpp"
#include "component/Velocity.hpp"
#include "component/factory/Factory.hpp"
#include "component/shape/Circle.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include <chrono>
#include <cstdint>
#include <random>
#include <vector>

void ecs::System::Flush(ecs::Impl &backBuffer) {
  std::vector<util::Entity> destroy{};
  backBuffer.Each<component::Lifetime>(
      [&](util::Entity entity, component::Lifetime &lifeTime) {
        if (lifeTime.lifeTime <= 0.1f)
          destroy.emplace_back(entity);
      });
  for (auto &id : destroy)
    backBuffer.Destroy(id);
}
void ecs::System::ParticleUpdate(ecs::Impl &buffer, float deltaTime) {
  // backBuffer.Each<component::Position, component::Velocity,
  //                 component::shape::Circle, component::Lifetime>(
  //     [&](util::Entity entity, component::Position &position,
  //         component::Velocity &velocity, component::shape::Circle &circle,
  //         component::Lifetime &lifeTime) {
  //       const auto lastPosition =
  //       frontBuffer.Get<component::Position>(entity); if (!lastPosition)
  //         return;
  //       const auto lastVelocity =
  //       frontBuffer.Get<component::Velocity>(entity); if (!lastVelocity)
  //         return;
  //       position.x = lastPosition->x + lastVelocity->dX * deltaTime;
  //       position.y = lastPosition->y + lastVelocity->dY * deltaTime;
  //       if (lifeTime.lifeTime >= 0) {
  //         velocity.dX *= 1 - deltaTime * 2;
  //         velocity.dY *= 1 - deltaTime * 2;
  //         lifeTime.lifeTime -= deltaTime * 3;
  //         circle.color -= 0x05050500;
  //       }
  //     });
  const auto &front = buffer;
  front.Each<component::Position, component::Velocity, component::shape::Circle,
             component::Lifetime>([&](util::Entity entity,
                                      const component::Position &position,
                                      const component::Velocity &velocity,
                                      const component::shape::Circle &circle,
                                      const component::Lifetime &lifetime) {
    auto newState =
        buffer.Get<component::Position, component::Velocity,
                   component::shape::Circle, component::Lifetime>(entity);
    if (!newState)
      return;
    auto &[pos, vel, shape, life] = *newState;
    pos.x = position.x + velocity.dX * deltaTime;
    pos.y = position.y + velocity.dY * deltaTime;
    if (lifetime.lifeTime >= -0) {
      vel.dX = velocity.dX * (1 - deltaTime);
      vel.dY = velocity.dY * (1 - deltaTime);
      life.lifeTime = lifetime.lifeTime - deltaTime;
      shape.color = circle.color - 0x02010100;
    }
  });
}

void ecs::System::Update(ecs::Impl &buffer, float deltaTime) {

  constexpr util::PosType POS_X{900};
  constexpr util::PosType POS_Y{500};
  constexpr float VELOCITY_X{300.f};
  constexpr float VELOCITY_Y{300.f};
  constexpr float RADIUS{20.f};
  constexpr uint32_t COLOR{0xFFFFFFFF};
  constexpr uint32_t states{2};
  constexpr float directionX[states]{-1.f, 1.f};
  constexpr float directionY[states]{-1.f, 1.f};
  static uint32_t stateX{0};
  static uint32_t stateY{0};
  // component::Factory::InsertParticle(
  //     backBuffer, {POS_X, POS_Y},
  //     {VELOCITY_X*directionX[(stateX++)%states],
  //     VELOCITY_Y *directionY[(++stateY)%states]}, {RADIUS,
  //     COLOR});

  std::mt19937::result_type seed = static_cast<std::mt19937::result_type>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  static std::mt19937 gen(seed);

  static std::uniform_real_distribution<float> distribution(-1.f, 1.f);
  static std::uniform_real_distribution<float> spawnRate{0, 1};
  Flush(buffer);
  ParticleUpdate(buffer, deltaTime);
  if (spawnRate(gen) < 0.01f) {

    component::Factory::InsertParticle(
        buffer, {POS_X, POS_Y},
        {VELOCITY_X * directionX[stateX], VELOCITY_Y * directionY[stateY]},
        {RADIUS, COLOR});
  }
}
