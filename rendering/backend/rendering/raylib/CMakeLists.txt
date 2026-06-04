# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME raylib_impl)
set(RAYLIB_VERSION 5.5)

find_package(raylib ${RAYLIB_VERSION} QUIET)
if(NOT raylib_FOUND)
  include(FetchContent)

  # Disable building extras BEFORE fetching
  set(BUILD_EXAMPLES
      OFF
      CACHE BOOL "" FORCE)
  set(BUILD_GAMES
      OFF
      CACHE BOOL "" FORCE)

  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if(NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES
        OFF
        CACHE BOOL "" FORCE)
  endif()
endif()

add_library(raylib_impl INTERFACE)

if(TARGET raylib)
  target_link_libraries(raylib_impl INTERFACE raylib)
else()
  message(FATAL_ERROR "raylib target not found after FetchContent")
endif()
