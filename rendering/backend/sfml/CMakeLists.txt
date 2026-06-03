
# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME sfml_impl)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(SOURCES
  SfmlRenderer.cpp
)


# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 4. Dependency Find / Fetch
# ------------------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML REQUIRED sfml-all)

# ------------------------------------------
# 5. Linking
# ------------------------------------------

target_include_directories(
  ${MODULE_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

# target_link_libraries(${MODULE_NAME} PUBLIC sfml::sfml)
target_link_libraries(${MODULE_NAME} PUBLIC project_settings)
target_link_libraries(${MODULE_NAME} PUBLIC ${ecs}_impl )
target_link_libraries(${MODULE_NAME} PUBLIC core)
target_link_libraries(${MODULE_NAME} PUBLIC component)

target_include_directories(${MODULE_NAME} PUBLIC ${SFML_INCLUDE_DIRS})
target_link_libraries(${MODULE_NAME} PUBLIC ${SFML_LIBRARIES})

