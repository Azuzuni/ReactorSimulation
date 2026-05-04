#pragma once
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "utils/RenderBackend.hpp"
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <mutex>
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
  ChernobylSimulator(ChernobylSimulator &&) = delete;
  ChernobylSimulator(const ChernobylSimulator &) = delete;
  ChernobylSimulator &operator=(ChernobylSimulator &&) = delete;
  ChernobylSimulator &operator=(const ChernobylSimulator &) = delete;

  static constexpr size_t kBufferCount{3};
  std::vector<Particle> mParticles[kBufferCount]{};
  std::vector<Fuel> mFuels[kBufferCount]{};
  std::atomic<uint8_t> mActiveBuffer{0};
  std::atomic<bool> mWorkerRunning{true};
  std::mutex mAccessMut{};

  RenderBackend mRenderer;

  void Logic();
  void Render();

public:
  /**
   * @brief Forwards Arguments on compiletime to the Renderer constructor
   */
  template <typename... Args>
  constexpr ChernobylSimulator(Args &&...args)
      : mRenderer{std::forward<Args>(args)...} {
    for(auto& each : mParticles)
      each.reserve(100000);
    for(auto& each : mFuels)
      each.reserve(100000);
  }
  ~ChernobylSimulator() = default;

  /**
   * @brief main loop keeping the program running
   */
  void Run();
};
