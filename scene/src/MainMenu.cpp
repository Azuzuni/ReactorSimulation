#include "scene/MainMenu.hpp"
#include "component/Position.hpp"
#include "component/shape/Rectangle.hpp"
#include "core/Color.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
using namespace scene;

void MainMenu::LoadScene(ecs::Impl &ecsImpl) {
  ecsImpl.DestroyAll();

  constexpr util::PosType POS_X{900};
  constexpr util::PosType POS_Y{500};
  constexpr float VELOCITY_X{600.f};
  constexpr float VELOCITY_Y{600.f};
  constexpr float RADIUS{20.f};
  constexpr uint32_t COLOR{0xFFFFFFFF};
  util::Entity entity{ecsImpl.Create()};
  ecsImpl.Add<component::Position>(entity, component::Position{750, 400});
  ecsImpl.Add<component::shape::Rectangle>(
      entity, component::shape::Rectangle{200, 100, color::BUTTON});
  // component::Factory::CreateParticle(ecsImpl, {POS_X, POS_Y},
  //                                    {VELOCITY_X, VELOCITY_Y}, {RADIUS,
  //                                    COLOR});
  // component::Factory::CreateParticle(ecsImpl, {POS_X, POS_Y + 30},
  //                                    {VELOCITY_X, VELOCITY_Y}, {RADIUS,
  //                                    COLOR});
  // component::Factory::CreateParticle(ecsImpl, {POS_X, POS_Y + 60},
  //                                    {VELOCITY_X, VELOCITY_Y}, {RADIUS,
  //                                    COLOR});
}
