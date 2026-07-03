#pragma once

#include "ecs/EcsImpl.hpp"
#include "utils/InputData.hpp"
namespace ecs {

class System {
  System() = delete;
  System(System &&) = delete;
  System(const System &) = delete;
  System &operator=(System &&) = delete;
  System &operator=(const System &) = delete;
  ~System() = delete;

  static void Flush(ecs::Impl &buffer);
  static void ParticleUpdate(ecs::Impl &buffer, float deltaTime);
  static void FuelUpdate(ecs::Impl &buffer, float deltaTime);
  static void ControlRodUpdate(ecs::Impl &buffer, InputData &inputData,
                               float deltaTime);

public:
  static void Update(ecs::Impl &buffer, InputData &InputData, float deltaTime);
};

}; // namespace ecs
