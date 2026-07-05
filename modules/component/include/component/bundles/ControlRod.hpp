#pragma once

#include "component/Position.hpp"
#include "component/shape/Rectangle.hpp"
#include "ecs/EcsImpl.hpp"
#include "utils/Configuration.hpp"
#include "utils/InputData.hpp"
#include <cstdint>

// =============================
// MACROS
// =============================

// macro for use with ecs::Impl::Each<BUNDLE>()
#ifndef COMPONENT_CONTROL_ROD_BUNDLE
#define COMPONENT_CONTROL_ROD_BUNDLE                                           \
  component::Position, component::shape::Rectangle, component::ControlRod
#else
#error "Redefinition of COMPONENT_CONTROL_ROD_BUNDLE"
#endif

// macro for use with ecs::Impl::Each<>(BUNDLE_VARS)
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

//! @brief component bundle and tag containing methods for ControlRod logic
struct ControlRod {
  //-----------------------------------
  // Constructors
  //-----------------------------------
  ControlRod() = default;
  ControlRod(ControlRod &&) = default;
  ControlRod(const ControlRod &) = default;
  ControlRod &operator=(ControlRod &&) = default;
  ControlRod &operator=(const ControlRod &) = default;
  ~ControlRod() = default;

  //-----------------------------------
  // Default values
  //-----------------------------------

  //! @TODO fix consistency across components
  static constexpr util::PosType RECTANGLE_WIDTH{20};
  static constexpr util::PosType RECTANGLE_HEIGHT{1000};
  static constexpr uint32_t RECTANGLE_COLOR{0x888888FF};
  static constexpr component::shape::Rectangle DEFAULT_RECTANGLE{
      RECTANGLE_WIDTH, RECTANGLE_HEIGHT, RECTANGLE_COLOR, false};

  //-----------------------------------
  // Methods
  //-----------------------------------

  //! @brief checks collision with Particles
  //!
  //! @TODO create universal Collider component and optimize collision check
  //!
  //! returns true if collided with something
  //! false if there is no collision
  //! @return bool
  static bool CollisionCheck(ecs::Impl &buffer, component::Position &position,
                             component::shape::Rectangle &rectangle,
                             float deltaTime);

  //! @brief moves control rods according to InputData
  //!
  //! @TODO make dedicated InputHandler with proper signals
  //!
  //! compares InputData::key with direction variable
  //! then acts accordingly to input
  //!
  //! @param inputData struct with information about pressed keys
  //! @param direction a KeyId enum with key for handled direction
  static void Move(ecs::Impl &buffer, InputData &inputData, KeyId direction,
                   float deltaTime);

  //! @brief Creates new entity and adds Bundle components to it
  //!
  //! @param position starting position of the entity
  //! @param rectangle shape of the entity and collider
  static void Create(ecs::Impl &buffer, const component::Position &position,
                     const component::shape::Rectangle &rectangle =
                         component::ControlRod::DEFAULT_RECTANGLE);

private:
  // since this class contains only static methods
  // this "cheapCheat" is a dirty solution to make this class copyable
  bool cheapCheat{};
};

}; // namespace component
