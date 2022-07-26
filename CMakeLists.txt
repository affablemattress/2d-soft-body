cmake_minimum_required (VERSION 3.8)

project ("2d-soft-body")

add_executable (2d-soft-body "src/main.cpp" "src/LOG.hpp" "src/V2.cpp" "src/V2.hpp" "src/Node.cpp" "src/Node.hpp" "src/Spring.cpp" "include/raudio.h" "include/raygui.h" "include/raylib.h" "include/raymath.h" "include/rlgl.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 2d-soft-body PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(2d-soft-body PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(2d-soft-body "${PROJECT_SOURCE_DIR}/lib/raylib.lib" winmm.lib)
