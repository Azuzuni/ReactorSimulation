#pragma once
#include "core/Color.hpp"
#include "ecs/EcsImpl.hpp"
#include "raylib.h"
#include "rendering/RenderIF.hpp"
#include "utils/InputData.hpp"

//! @brief Raylib implementation of RenderIF
class RaylibRender : public RenderIF<RaylibRender> {

  //! friend access allows parent to call Impl methods
  friend class RenderIF<RaylibRender>;

  //-----------------------------------
  // Private Constructors
  //-----------------------------------
  RaylibRender() = default;
  RaylibRender(const RaylibRender &) = delete;
  RaylibRender &operator=(const RaylibRender &) = delete;

  //-----------------------------------
  // Member Methods
  //-----------------------------------

  //! @brief Implementation of GetWidthOfWindow()
  //! @see RenderIF
  int GetWidthOfWindowImpl() const noexcept;

  //! @brief Implementation of GetHeightOfWindow()
  //! @see RenderIF
  int GetHeightOfWindowImpl() const noexcept;

  //! @brief Implementation of ShouldClose()
  //! @see RenderIF
  bool ShouldCloseImpl() const noexcept;

  //! @brief function that converts color::Color into raylib Color
  constexpr Color ToColor(const color::Color &rgba) const noexcept;

  //! @brief draws all components with position and circle components
  void DrawCircle(const ecs::Impl &buffer) const noexcept;

  //! @brief draws all components with position and rectangle components
  void DrawRectangle(const ecs::Impl &buffer) const noexcept;

  //! @brief checks for Input information and return struct
  //! @see InputData
  //! @return InputData
  InputData InputHandler() const noexcept;

  //! @brief Implementation of Update()
  //! @see RenderIF
  InputData UpdateImpl(const ecs::Impl &buffer) const noexcept;

public:
  RaylibRender(int width, int height, const char *title);
  RaylibRender(RaylibRender &&) = default;
  RaylibRender &operator=(RaylibRender &&) = default;
  ~RaylibRender();
};
