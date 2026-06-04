# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME core)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(HEADERS include/core/Color.h include/core/ReactorSimulator.h)
set(SOURCES src/ReactorSimulator.cpp)

# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 1. Linking
# ------------------------------------------

target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ecs)
target_link_libraries(${MODULE_NAME} PUBLIC rendering)
target_link_libraries(${MODULE_NAME} PUBLIC scene)
