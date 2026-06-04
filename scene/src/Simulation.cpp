#include "scene/Simulation.hpp"
#include "component/factory/Factory.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include <chrono>
#include <cstdint>
#include <random>
using namespace scene;
namespace cmp = component;
void Simulation::LoadScene(ecs::Impl &ecsImpl) {
  ecsImpl.DestroyAll();
  constexpr util::PosType POS_X{900};
  constexpr util::PosType POS_Y{500};
  constexpr float VELOCITY_X{600.f};
  constexpr float VELOCITY_Y{600.f};
  constexpr float RADIUS{20.f};
  constexpr uint32_t COLOR{0xFFFFFFFF};

  std::mt19937::result_type seed = static_cast<std::mt19937::result_type>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count());
  std::mt19937 gen(seed);

  std::uniform_int_distribution<int32_t> distribution(0, 1);
  for (int32_t i{}; i < 4; ++i) {
    float signX = (distribution(gen) == 0) ? -1.f : 1.f;
    float signY = (distribution(gen) == 0) ? -1.f : 1.f;
    cmp::Factory::InsertParticle(
        ecsImpl,
        {POS_X + distribution(gen) * 10, POS_Y + distribution(gen) * 10},
        {VELOCITY_X * signX, VELOCITY_Y * signY}, {RADIUS, COLOR});
  }
  // cmp::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y},
  //                              {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
  // cmp::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y + 30},
  //                              {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
  // cmp::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y + 60},
  //                              {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
}
