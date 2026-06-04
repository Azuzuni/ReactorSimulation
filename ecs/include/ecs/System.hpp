#pragma once

#include "component/factory/Factory.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include <vector>
namespace ecs {

struct EntityQueue {
  std::vector<component::Type> spawnQueue{};
  std::vector<util::Entity> killQueue{};
};

class System {
  System() = delete;
  System(System &&) = delete;
  System(const System &) = delete;
  System &operator=(System &&) = delete;
  System &operator=(const System &) = delete;
  ~System() = delete;

  static void Flush(ecs::Impl &buffer);
  static void ParticleUpdate(ecs::Impl &buffer, float deltaTime);

public:
  static void Update(ecs::Impl &buffer, float deltaTime);
};

}; // namespace ecs
