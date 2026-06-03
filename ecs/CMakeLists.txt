# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME ecs)
add_subdirectory(backend/${ecs})
# ------------------------------------------
# 2. Files
# ------------------------------------------

set(HEADERS 
  include/ecs/EcsIF.hpp
  include/ecs/EcsImpl.hpp
  include/ecs/System.h
)
set(SOURCES
  src/System.cpp
)

# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 4. Linking
# ------------------------------------------
target_include_directories( ${MODULE_NAME} PRIVATE backend )
target_include_directories( ${MODULE_NAME} PUBLIC include )

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ${ecs}_impl )
