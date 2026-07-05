# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(ENTT_VERSION v3.16.0)

find_package(EnTT CONFIG QUIET)

if(NOT EnTT_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    entt
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG ${ENTT_VERSION})

  FetchContent_MakeAvailable(entt)
endif()

add_library(entt_impl INTERFACE)

if(TARGET EnTT::EnTT)
  target_link_libraries(entt_impl INTERFACE EnTT::EnTT)
elseif(TARGET entt)
  target_link_libraries(entt_impl INTERFACE entt)
else()
  message(FATAL_ERROR "EnTT target not found after FetchContent")
endif()
