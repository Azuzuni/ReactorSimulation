#pragma once

#include "ecs/EcsImpl.hpp"
namespace scene {

enum SceneEnum {
  MAIN_MENU = 0,
  SIMULATION = 1,
};

class SceneIF {
public:
  SceneIF() = default;
  SceneIF(SceneIF &&) = default;
  SceneIF(const SceneIF &) = default;
  SceneIF &operator=(SceneIF &&) = default;
  SceneIF &operator=(const SceneIF &) = default;
  virtual ~SceneIF() = default;

  virtual void LoadScene(ecs::Impl &) = 0;
};

}; // namespace scene
