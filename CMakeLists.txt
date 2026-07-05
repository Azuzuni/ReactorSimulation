cmake_minimum_required(VERSION 3.20)
project(myProject)

# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(APP_NAME ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(RENDERING
    "raylib"
    CACHE STRING "Rendering backend")
set(ECS
    "entt"
    CACHE STRING "ECS implementation")
set(BUILD_TESTS
    ON
    CACHE BOOL "Build unit tests")

add_library(project_settings INTERFACE)
set_target_properties(
  project_settings
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED YES
             CXX_EXTENSIONS NO)
target_compile_definitions(project_settings INTERFACE RENDERING_${RENDERING})
target_compile_definitions(project_settings INTERFACE ECS_${ECS})

message(STATUS "rendering='${RENDERING}'")
message(STATUS "ecs='${ECS}'")

# ------------------------------------------
# 1. Libraries
# ------------------------------------------
add_subdirectory(modules/rendering)
add_subdirectory(modules/ecs)
add_subdirectory(modules/utils)
add_subdirectory(modules/scene)
add_subdirectory(modules/component)
add_subdirectory(modules/core)

# ------------------------------------------
# 1. Exec
# ------------------------------------------

add_executable(${APP_NAME} app/main.cpp)

# ------------------------------------------
# 1. Linking
# ------------------------------------------

target_link_libraries(${APP_NAME} PRIVATE project_settings)
target_link_libraries(${APP_NAME} PRIVATE core)

# ------------------------------------------
# 1. LSP command detection
# ------------------------------------------

if(CMAKE_EXPORT_COMPILE_COMMANDS)
    add_custom_target(
    copy_compile_commands ALL
    COMMAND
      ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_BINARY_DIR}/compile_commands.json"
      "${CMAKE_SOURCE_DIR}/compile_commands.json"
    COMMENT "Copying compile_commands.json to project root for LSP")
endif()
