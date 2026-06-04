# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME component)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(HEADERS
    include/component/shape/Circle.h
    include/component/shape/Rectangle.h
    include/component/factory/Factory.h
    include/component/Lifetime.hpp
    include/component/Position.h
    include/component/Types.hpp
    include/component/Velocity.h)

set(SOURCES src/factory/Factory.cpp)

# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 1. Linking
# ------------------------------------------

target_include_directories(${MODULE_NAME} PUBLIC include)

target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC ecs)
