#pragma once

#include "scene/SceneIF.h"
namespace scene {

class MainMenu : public SceneIF {
public:
  MainMenu() = default;
  MainMenu(MainMenu &&) = default;
  MainMenu(const MainMenu &) = default;
  MainMenu &operator=(MainMenu &&) = default;
  MainMenu &operator=(const MainMenu &) = default;
  virtual ~MainMenu() = default;

  void LoadScene(ecs::Impl &) override;
};

}; // namespace scene
