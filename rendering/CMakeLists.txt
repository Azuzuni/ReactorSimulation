# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME rendering)
add_subdirectory(backend/${rendering})

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(HEADERS
  include/rendering/RenderIF.hpp
  include/rendering/RenderImpl.h
)

set(SOURCES
  src/dummy.cpp
)

# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 4. Linking
# ------------------------------------------

target_include_directories(
  ${MODULE_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ${rendering}_impl )
