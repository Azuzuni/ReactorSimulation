# ------------------------------------------
# 1. Variables
# ------------------------------------------

set(MODULE_NAME entt_impl)
set(ENTT_VERSION v3.16.0)

# ------------------------------------------
# 2. Files
# ------------------------------------------

set(SOURCES
  EnTTimpl.cpp
)

# ------------------------------------------
# 3. Library
# ------------------------------------------

add_library(${MODULE_NAME} STATIC ${SOURCES})

# ------------------------------------------
# 4. Dependency Find / Fetch
# ------------------------------------------

find_package(EnTT CONFIG QUIET)

if (NOT EnTT_FOUND)
  include(FetchContent)

  FetchContent_Declare(
    entt
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    GIT_REPOSITORY https://github.com/skypjack/entt.git
    GIT_TAG ${ENTT_VERSION}
  )

  FetchContent_MakeAvailable(entt)
endif()

# ------------------------------------------
# 5. Linking
# ------------------------------------------

target_include_directories(
  ${MODULE_NAME}
  PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${MODULE_NAME} PUBLIC EnTT::EnTT)
