#include "scene/MainMenu.h"
#include "Color.h"
#include "component/Factory.h"
#include "component/Position.h"
#include "component/shape/Rectangle.h"
#include "ecs/EcsImpl.h"
#include "utils/Configuration.h"
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
  component::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y},
                               {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
  component::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y + 30},
                               {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
  component::Factory::InsertParticle(ecsImpl, {POS_X, POS_Y + 60},
                               {VELOCITY_X, VELOCITY_Y}, {RADIUS, COLOR});
}
