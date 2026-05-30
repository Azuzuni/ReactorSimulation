#pragma once

#include "component/Factory.h"
#include "ecs/EcsImpl.h"
#include "utils/Configuration.h"
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
