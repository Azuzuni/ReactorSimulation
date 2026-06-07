# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME component)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(SOURCES include/component/bundles/Particle.cpp
            include/component/bundles/Fuel.cpp)

# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 1. Linking
# ------------------------------------------

target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC ecs)
