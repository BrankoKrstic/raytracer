add_library(raytracerlib STATIC lib.cpp)

target_include_directories(raytracerlib
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}
  )