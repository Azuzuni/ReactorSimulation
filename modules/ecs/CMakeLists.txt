# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME ecs)
# ------------------------------------------
# 1. Files
# ------------------------------------------

set(SOURCES src/System.cpp)

add_subdirectory(backend/ecs/${ECS})
# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 1. Linking
# ------------------------------------------
target_include_directories(${MODULE_NAME} PUBLIC backend)
target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC component)
target_link_libraries(${MODULE_NAME} PUBLIC ${ECS}_impl)
target_sources(${MODULE_NAME} PUBLIC backend/ecs/${ECS}/Implementation.hpp)
