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

add_library(project_settings INTERFACE)
set_target_properties(project_settings PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

set(rendering "raylib" CACHE STRING "Rendering backend")
set(ecs "entt" CACHE STRING "ECS implementation")


# ------------------------------------------
# 2. Libraries
# ------------------------------------------
add_subdirectory(component)
add_subdirectory(core)
add_subdirectory(ecs)
add_subdirectory(physics)
add_subdirectory(rendering)
add_subdirectory(utils)

# ------------------------------------------
# 3. Exec
# ------------------------------------------

if(WIN32)
  add_executable(${APP_NAME} WIN32 app/winmain.cpp)
else()
  add_executable(${APP_NAME} app/main.cpp)
endif()

# ------------------------------------------
# 4. Implementation selection
# ------------------------------------------

target_compile_definitions(project_settings INTERFACE RENDERING_${rendering})
target_compile_definitions(project_settings INTERFACE ECS_${ecs})

# ------------------------------------------
# 5. Linking
# ------------------------------------------

target_link_libraries( ${APP_NAME} PRIVATE project_settings)
target_link_libraries( ${APP_NAME} PRIVATE core)
# target_link_libraries( ${APP_NAME} PRIVATE component)
# target_link_libraries( ${APP_NAME} PRIVATE physics)
# target_link_libraries( ${APP_NAME} PRIVATE ${rendering})
# target_link_libraries( ${APP_NAME} PRIVATE ${ecs})
# target_link_libraries( ${APP_NAME} PRIVATE utils)
