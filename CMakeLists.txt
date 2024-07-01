cmake_minimum_required(VERSION 3.15)
project(znet CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -pthread")

include(FetchContent)
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.81.0
)
FetchContent_MakeAvailable(boost)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)
