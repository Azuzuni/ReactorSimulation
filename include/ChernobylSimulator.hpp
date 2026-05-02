#pragma once
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "utils/RenderBackend.hpp"
#include <utility>
#include <vector>

/**
 * @file
 * @brief Core class containing logic and main loop
 *
 * @class ChernobylSimulator
 * @brief core class including main loop with:
 * - Logic Implementation
 * - Render calls through RenderBackend API (RendererIF.hpp)
 */
class ChernobylSimulator {
  ChernobylSimulator() = delete;
  ChernobylSimulator(const ChernobylSimulator &) = delete;
  ChernobylSimulator &operator=(const ChernobylSimulator &) = delete;

  std::vector<Particle> mParticles{};
  std::vector<Fuel> mFuels{};
  RenderBackend mRenderer;

  void Logic();
  void Render();

public:
  /**
   * @brief Forwards Arguments on compiletime to the Renderer constructor
   */
  template <typename... Args>
  constexpr ChernobylSimulator(Args &&...args)
      : mRenderer{std::forward<Args>(args)...} {}
  ChernobylSimulator(ChernobylSimulator &&) = default;
  ChernobylSimulator &operator=(ChernobylSimulator &&) = default;
  ~ChernobylSimulator() = default;

  /**
   * @brief main loop keeping the program running
   */
  void Run();
};
