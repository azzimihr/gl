cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_C_COMPILER "clang")

set(CMAKE_CXX_FLAGS "-stdlib=libc++" CACHE STRING "C++ compiler flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "-stdlib=libc++" CACHE STRING "Executable linker flags" FORCE)

project(app)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
file(GLOB_RECURSE SOURCES "*.cpp" "*.c")
list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_SOURCE_DIR}/build/*")
add_executable(app ${SOURCES})

target_compile_options(app PRIVATE
  -Wall -Wextra -Wpedantic -Werror
  -O3 -g
  -march=native
  -fmodules
  -fmodules-cache-path=${CMAKE_BINARY_DIR}/modules-cache
)

target_link_libraries(app glfw GL X11 pthread Xrandr Xi dl stdc++exp)