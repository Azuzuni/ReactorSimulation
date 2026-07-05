#pragma once

#include "ecs/EcsImpl.hpp"
namespace scene {

//! @brief enum containing scene IDs
//! @TODO replace with scene loader
//! @see ReactorSimulator
enum SceneEnum {
  MAIN_MENU = 0,
  SIMULATION = 1,
};

//! @brief Scene interface for presets
//! @TODO replace with scene loader
class SceneIF {
public:
  SceneIF() = default;
  SceneIF(SceneIF &&) = default;
  SceneIF(const SceneIF &) = default;
  SceneIF &operator=(SceneIF &&) = default;
  SceneIF &operator=(const SceneIF &) = default;
  virtual ~SceneIF() = default;

  //! @brief interface for loading scenes
  virtual void LoadScene(ecs::Impl &buffer) = 0;
};

}; // namespace scene
