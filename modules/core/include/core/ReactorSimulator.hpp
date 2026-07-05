#pragma once
#include "ecs/EcsImpl.hpp"
#include "rendering/RenderImpl.hpp"
#include "scene/SceneIF.hpp"
#include "utils/InputData.hpp"
#include <memory>
#include <unordered_map>

//! @brief Core class of the simulation
//!
//! ReactorSimulator handles Logic and Rendering of the simulation
//! call Run() method to start everything.
class ReactorSimulator {

  //! kTickRate fixed logic update rate
  //! @see Logic()
  const float kTickRate = 60.0f;

  //! kDt fixed deltatime
  //! @see Logic()
  const float kDt = 1.0f / kTickRate;

  ReactorSimulator() = delete;
  ReactorSimulator(ReactorSimulator &&) = delete;
  ReactorSimulator(const ReactorSimulator &) = delete;
  ReactorSimulator &operator=(ReactorSimulator &&) = delete;
  ReactorSimulator &operator=(const ReactorSimulator &) = delete;

  //! @brief contains map of available scenes
  //!
  //! @TODO replace map of scenes with scene loader
  //! that reads scene definitions from JSON
  //!
  //! key @see SceneEnum
  //! value @see SceneIF
  std::unordered_map<scene::SceneEnum, std::unique_ptr<scene::SceneIF>>
      mScenes{};

  //! mEcs buffer containing data for logic and rendering
  //! @see ecs::Impl
  ecs::Impl mEcs{};

  //! mRenderer selected implementation Renderer (CRTP)
  //! @see RenderBackend
  RenderBackend mRenderer;

  //! mInputData Struct keeping input informations returned by
  //! mRenderer.Update()
  //! @see RenderBackend
  InputData mInputData{};

  //! @brief operates on mEcs buffer to prepare frame to render
  //!
  //! @see ecs::Impl
  //! @see RenderBackend
  void Logic();

  //! @brief renders components representing shapes from mEcs
  //!
  //! @see ecs::Impl
  //! @see Logic()
  void Render();

public:
  //! @brief Starting point of simulation
  void Run();

  //! @brief Initializes values, and loads scenes
  //!
  //! @param width is the width of the starting window
  //! @param height is the height of the starting window
  //! @param title is the name of the window
  ReactorSimulator(int width, int height, const char *title);
  ~ReactorSimulator() = default;
};
