# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME rendering)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(SOURCES backend/rendering/${RENDERING}/Implementation.cpp)

add_subdirectory(backend/rendering/${RENDERING})

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
target_link_libraries(${MODULE_NAME} PUBLIC component)
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC ecs)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC ${RENDERING}_impl)
target_sources(${MODULE_NAME}
               PUBLIC backend/rendering/${RENDERING}/Implementation.hpp)
