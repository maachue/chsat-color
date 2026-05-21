cmake_minimum_required(VERSION 3.30)
project(chsat-color VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

add_executable(${PROJECT_NAME}
  src/main.cc
  src/cli.cc
)

find_package(fmt QUIET)

if(NOT fmt_FOUND)
  FetchContent_Declare(
      fmt
      GIT_REPOSITORY https://github.com/fmtlib/fmt
      GIT_TAG        12.1.0)
  FetchContent_MakeAvailable(fmt)
endif()

target_link_libraries(${PROJECT_NAME} fmt::fmt)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/include")
