# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME utils)

# ------------------------------------------
# 1. Files
# ------------------------------------------

set(HEADERS include/utils/Configuration.hpp)

set(SOURCES Configuration.cpp)

# ------------------------------------------
# 1. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES} ${HEADERS})

# ------------------------------------------
# 1. Linking
# ------------------------------------------
target_include_directories(${MODULE_NAME} PUBLIC include)
target_link_libraries(${MODULE_NAME} INTERFACE project_settings)
