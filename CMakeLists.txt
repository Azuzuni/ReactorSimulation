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

add_subdirectory(rendering)
add_subdirectory(ecs)
add_subdirectory(utils)
add_subdirectory(scene)
add_subdirectory(component)
add_subdirectory(core)

# ------------------------------------------
# 1. Exec
# ------------------------------------------

add_executable(${APP_NAME} app/main.cpp)

# ------------------------------------------
# 1. Linking
# ------------------------------------------

target_link_libraries(${APP_NAME} PRIVATE project_settings)
target_link_libraries(${APP_NAME} PRIVATE core)
