# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME utils)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(HEADERS
  Configuration.hpp
)

set(SOURCES
)

# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} INTERFACE ${SOURCES} ${HEADERS})

# ------------------------------------------
# 4. Linking
# ------------------------------------------

target_link_libraries(${MODULE_NAME} INTERFACE project_settings)
