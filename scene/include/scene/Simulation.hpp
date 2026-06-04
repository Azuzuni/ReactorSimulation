
#pragma once

#include "scene/SceneIF.hpp"
namespace scene {

class Simulation : public SceneIF {
public:
  Simulation() = default;
  Simulation(Simulation &&) = default;
  Simulation(const Simulation &) = default;
  Simulation &operator=(Simulation &&) = default;
  Simulation &operator=(const Simulation &) = default;
  virtual ~Simulation() = default;

  void LoadScene(ecs::Impl &) override;
};

}; // namespace scene
