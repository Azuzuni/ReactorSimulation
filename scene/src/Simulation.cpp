#include "scene/Simulation.hpp"
#include "component/Position.hpp"
#include "component/bundles/Fuel.hpp"
#include "ecs/EcsImpl.hpp"
using namespace scene;
void Simulation::LoadScene(ecs::Impl &buffer) {
  buffer.DestroyAll();
  constexpr float WIDTH{1920};
  constexpr float HEIGHT{1080};
  for (int y{1}; y <= 8; ++y)
    for (int i{1}; i <= 8; ++i)
      component::Fuel::Create(buffer, {(WIDTH / 9) * i, (HEIGHT / 9) * y});
}
