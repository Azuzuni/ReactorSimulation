
# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME raylib_impl)
set(RAYLIB_VERSION 5.5)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(SOURCES
  RaylibRenderer.cpp
)


# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 4. Dependency Find / Fetch
# ------------------------------------------

find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)

  # Disable building extras BEFORE fetching
  set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
  endif()
endif()

# ------------------------------------------
# 5. Linking
# ------------------------------------------

target_include_directories(
  ${MODULE_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${MODULE_NAME} PUBLIC raylib)
target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ${ECS_IMPL}_impl )
