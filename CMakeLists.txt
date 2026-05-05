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
set(RENDERING_BACKEND "raylib" CACHE STRING "Rendering backend")

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(SOURCES
  src/ReactorSimulator.cpp
  src/main.cpp
)

# IDE compatybility thing
set(HEADERS
  include/ReactorSimulator.hpp
  include/elements/Square.hpp
  include/elements/Particle.hpp
  include/rendering/raylib/RaylibRender.hpp
  include/rendering/RendererIF.hpp
  include/utils/Color.hpp
  include/utils/Configuration.hpp
  include/utils/RenderBackend.hpp
)



# ------------------------------------------
# 3. Libraries
# ------------------------------------------
add_subdirectory(src/rendering/${RENDERING_BACKEND})
add_subdirectory(src/physics/)


# ------------------------------------------
# 4. Exec
# ------------------------------------------

add_executable(
  ${APP_NAME} 
  ${SOURCES}
  ${HEADERS}
)

# ------------------------------------------
# 5. Linking
# ------------------------------------------

target_include_directories( ${APP_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include )
target_link_libraries( ${APP_NAME} ${RENDERING_BACKEND}_impl )
target_link_libraries( ${APP_NAME} physics)


# ------------------------------------------
# 6. Implementation selection
# ------------------------------------------

target_compile_definitions(${APP_NAME} PRIVATE kRenderingBackend_${RENDERING_BACKEND})
