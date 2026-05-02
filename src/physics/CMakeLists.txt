# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME physics)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(SOURCES
  Collision.cpp
)


# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 4. Linking
# ------------------------------------------

target_include_directories(
  ${MODULE_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

