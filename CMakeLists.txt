# CMakeList.txt : CMake project for mass-spring-damper-pendulum, include source and define
# project specific logic here.

cmake_minimum_required (VERSION 3.8)

project ("mass-spring-damper-pendulum")

add_executable (mass-spring-damper-pendulum "src/main.cpp" "src/LOG.hpp" "src/V2.cpp" "src/V2.hpp" "src/Node.cpp" "src/Node.hpp" "src/Spring.cpp" "include/raudio.h" "include/raygui.h" "include/raylib.h" "include/raymath.h" "include/rlgl.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET mass-spring-damper-pendulum PROPERTY CXX_STANDARD 20)
endif()

target_include_directories(mass-spring-damper-pendulum PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_link_libraries(mass-spring-damper-pendulum "${PROJECT_SOURCE_DIR}/lib/raylib.lib" winmm.lib)
