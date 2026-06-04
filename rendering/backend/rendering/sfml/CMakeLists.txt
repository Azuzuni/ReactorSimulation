set(SFML_VERSION 3.0.1)

find_package(SFML CONFIG QUIET COMPONENTS System Window Graphics)

if(NOT SFML_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG ${SFML_VERSION})

  FetchContent_MakeAvailable(sfml)
endif()

add_library(sfml_impl INTERFACE)

target_link_libraries(sfml_impl INTERFACE SFML::System SFML::Window
                                          SFML::Graphics)
