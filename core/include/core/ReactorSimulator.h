#pragma once
#include "ecs/EcsImpl.h"
#include "rendering/RenderImpl.hpp"
#include "scene/SceneIF.h"
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include <utility>

//! Core class for simulation
/*!
 * This class works as entry point to the project
 * Run() to initialize the simulation.
 */
class ReactorSimulator {

  const float kTickRate = 120.0f;
  const float kDt = 1.0f / kTickRate;

  ReactorSimulator() = delete;
  ReactorSimulator(ReactorSimulator &&) = delete;
  ReactorSimulator(const ReactorSimulator &) = delete;
  ReactorSimulator &operator=(ReactorSimulator &&) = delete;
  ReactorSimulator &operator=(const ReactorSimulator &) = delete;

  //! @param mScenes
  /*!
   * Contains all available scenes
   * @param key -> @sa SceneEnum
   * @param value -> @sa SceneIF
   */
  std::unordered_map<int, std::unique_ptr<scene::SceneIF>> mScenes{};


  //! @param mEcs -> buffers containing data for logic and rendering
  ecs::Impl mEcs{};

  //! @param mRenderer -> rendering
  RenderBackend mRenderer;

  void Logic();
  void Render();
  
  /**
   * @brief main loop keeping the program running
   */
  void Run();

public:
  /**
   * @brief Forwards Arguments on compiletime to the Renderer constructor
   */
  ReactorSimulator(int, int, const char*);
  ~ReactorSimulator() = default;



};
