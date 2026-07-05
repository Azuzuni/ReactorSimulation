
/**
 * @file
 * @brief configuration implementation for using directives
 * PosType, colors and other miscelanious small things
 */

#pragma once
#include <cstdint>
namespace util {

//! @brief position type representing single coordinate
//         PosType = float
using PosType = float;

//! @brief universal ID type for entities
//!        Entity = uint32_t
using Entity = uint32_t;

//! @brief width used for computing before scaling with screen
//! @TODO implement scaling
constexpr PosType COMPUTED_WIDTH{};

//! @brief height used for computing before scaling with screen
//! @TODO implement scaling
constexpr PosType COMPUTED_HEIGHT{};

}; // namespace util
