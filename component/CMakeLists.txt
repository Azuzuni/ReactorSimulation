# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME component)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(HEADERS 
  shape/Circle.h
  shape/Rectangle.h
  factory/Factory.h
  Lifetime.hpp
  Position.h
  Types.hpp
  Velocity.h
)

set(SOURCES
  factory/Factory.cpp
)


# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 4. Linking
# ------------------------------------------

target_include_directories( ${MODULE_NAME} PUBLIC factory )
target_include_directories( ${MODULE_NAME} PUBLIC shape )


target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC ${ecs} )
