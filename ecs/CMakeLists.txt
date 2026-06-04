# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME ecs)
# ------------------------------------------
# 1. Files
# ------------------------------------------

set(HEADERS include/ecs/EcsIF.hpp include/ecs/EcsImpl.hpp include/ecs/System.h)
set(SOURCES src/System.cpp)

add_subdirectory(backend/ecs/${ecs})
# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 1. Linking
# ------------------------------------------
target_include_directories(${MODULE_NAME} PUBLIC backend)
target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC component)
target_link_libraries(${MODULE_NAME} PUBLIC ${ecs}_impl)
target_sources(${MODULE_NAME} PUBLIC backend/ecs/${ecs}/Implementation.hpp)
