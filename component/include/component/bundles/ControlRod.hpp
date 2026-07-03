#pragma once

#include "component/Position.hpp"
#include "component/shape/Circle.hpp"
#include "component/shape/Rectangle.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include "utils/InputData.hpp"
#include <cstdint>

// =============================
// MACROS
// =============================

#ifndef COMPONENT_CONTROL_ROD_BUNDLE
#define COMPONENT_CONTROL_ROD_BUNDLE                                           \
  component::Position, component::shape::Rectangle, component::ControlRod
#else
#error "Redefinition of COMPONENT_CONTROL_ROD_BUNDLE"
#endif

#ifndef COMPONENT_CONTROL_ROD_BUNDLE_VARS
#define COMPONENT_CONTROL_ROD_BUNDLE_VARS(position, rectangle, controlRod)     \
  component::Position &position, component::shape::Rectangle &rectangle,       \
      component::ControlRod &controlRod
#else
#error "Redefinition of COMPONENT_CONTROL_ROD_BUNDLE_VARS"
#endif

// =============================
// COMPONENT
// =============================

namespace component {

struct ControlRod {
  ControlRod() = default;
  ControlRod(ControlRod &&) = default;
  ControlRod(const ControlRod &) = default;
  ControlRod &operator=(ControlRod &&) = default;
  ControlRod &operator=(const ControlRod &) = default;
  ~ControlRod() = default;

  static constexpr util::PosType RECTANGLE_WIDTH{50};
  static constexpr util::PosType RECTANGLE_HEIGHT{1000};
  static constexpr uint32_t RECTANGLE_COLOR{0xFF0000FF};
  static constexpr component::shape::Rectangle DEFAULT_RECTANGLE{
      RECTANGLE_WIDTH, RECTANGLE_HEIGHT, RECTANGLE_COLOR, false};

  static bool CollisionCheck(ecs::Impl &buffer, component::Position &position,
                             component::shape::Rectangle &rectangle,
                             float deltaTime);
  static void Move(ecs::Impl &buffer, InputData &InputData, KeyId direction,
                   float deltaTime);
  static void Create(ecs::Impl &buffer, const component::Position &position,
                     const component::shape::Rectangle &rectangle =
                         component::ControlRod::DEFAULT_RECTANGLE);

private:
  bool cheapCheat{};
};

}; // namespace component
