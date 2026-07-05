// contains AI GENERATED code
#pragma once

#include <SFML/Graphics.hpp>
#include <cstdint>

#include "core/Color.hpp"
#include "ecs/EcsImpl.hpp"
#include "rendering/RenderIF.hpp"
#include "utils/InputData.hpp"

//! @brief SFML implementation of RenderIF
class SfmlRender : public RenderIF<SfmlRender> {

  //! friend access allows parent to call Impl methods
  friend class RenderIF<SfmlRender>;

  //-----------------------------------
  // Private Constructors
  //-----------------------------------
  SfmlRender() = default;
  SfmlRender(const SfmlRender &) = delete;
  SfmlRender &operator=(const SfmlRender &) = delete;

  //-----------------------------------
  // Member Variables
  //-----------------------------------
  sf::RenderWindow window;

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

  //! @brief function that converts color::Color into sf::Color
  sf::Color ToColor(const color::Color &rgba) const noexcept;

  //! @brief draws all components with position and circle components
  void DrawCircle(const ecs::Impl &buffer) noexcept;

  //! @brief draws all components with position and rectangle components
  void DrawRectangle(const ecs::Impl &buffer) noexcept;

  //! @brief Implementation of Update()
  //! @see RenderIF
  InputData UpdateImpl(const ecs::Impl &buffer) noexcept;

public:
  SfmlRender(int width, int height, const char *title);

  SfmlRender(SfmlRender &&) = default;
  SfmlRender &operator=(SfmlRender &&) = default;

  ~SfmlRender();
};
