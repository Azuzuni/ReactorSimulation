# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME rendering)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(HEADERS include/rendering/RenderIF.hpp include/rendering/RenderImpl.h)

set(SOURCES backend/rendering/${rendering}/Implementation.cpp)

add_subdirectory(backend/rendering/${rendering})

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
target_link_libraries(${MODULE_NAME} PUBLIC component)
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC ecs)
target_link_libraries(${MODULE_NAME} PUBLIC utils)
target_link_libraries(${MODULE_NAME} PUBLIC ${rendering}_impl)
target_sources(${MODULE_NAME}
               PUBLIC backend/rendering/${rendering}/Implementation.hpp)
