#include "scene/Simulation.hpp"
#include "component/Position.hpp"
#include "component/bundles/ControlRod.hpp"
#include "component/bundles/Fuel.hpp"
#include "ecs/EcsImpl.hpp"
using namespace scene;
void Simulation::LoadScene(ecs::Impl &buffer) {
  buffer.DestroyAll();
  constexpr float WIDTH{1920};
  constexpr float HEIGHT{1080};
  for (int y{1}; y <= 8; ++y)
    for (int i{1}; i <= 8; ++i)
      component::Fuel::Create(buffer, {200.f * i, 100.f * y});

  component::ControlRod::Create(buffer, {100.f - 25, 0});
  component::ControlRod::Create(buffer, {500.f - 25, 0});
  component::ControlRod::Create(buffer, {900.f - 25, 0});
  component::ControlRod::Create(buffer, {1300.f - 25, 0});
  component::ControlRod::Create(buffer, {1700.f - 25, 0});
}
