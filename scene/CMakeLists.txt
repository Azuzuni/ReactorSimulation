# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME scene)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(HEADERS 
  include/scene/MainMenu.h
  include/scene/SceneIF.h
  include/scene/Simulation.h
)
set(SOURCES
  src/MainMenu.cpp
  src/Simulation.cpp
)

# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 4. Linking
# ------------------------------------------

target_include_directories( ${MODULE_NAME} PUBLIC include )

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ecs )
target_link_libraries(${MODULE_NAME} PUBLIC rendering )
