#pragma once
#include "elements/Particle.hpp"
#include "elements/Square.hpp"
#include "utils/RenderBackend.hpp"
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

/**
 * @file
 * @brief Core class containing logic and main loop
 *
 * @class ReactorSimulator
 * @brief core class including main loop with:
 * - Logic Implementation
 * - Render calls through RenderBackend API (RendererIF.hpp)
 */
class ReactorSimulator {
  ReactorSimulator() = delete;
  ReactorSimulator(ReactorSimulator &&) = delete;
  ReactorSimulator(const ReactorSimulator &) = delete;
  ReactorSimulator &operator=(ReactorSimulator &&) = delete;
  ReactorSimulator &operator=(const ReactorSimulator &) = delete;

  static constexpr size_t kBufferCount{2};
  std::atomic<uint8_t> mFrontBuffer{0};
  std::atomic<bool> mFrameReady{false};
  std::atomic<bool> mWorkerRunning{true};

  std::vector<Particle> mParticles[kBufferCount]{};
  std::vector<Fuel> mFuels[kBufferCount]{};

  RenderBackend mRenderer;

  void Logic();
  void Render();

public:
  /**
   * @brief Forwards Arguments on compiletime to the Renderer constructor
   */
  template <typename... Args>
  constexpr ReactorSimulator(Args &&...args)
      : mRenderer{std::forward<Args>(args)...} {
    for(auto& each : mParticles)
      each.reserve(100000);
    for(auto& each : mFuels)
      each.reserve(100000);
  }
  ~ReactorSimulator() = default;

  /**
   * @brief main loop keeping the program running
   */
  void Run();
};
