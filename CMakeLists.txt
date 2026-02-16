cmake_minimum_required(VERSION 3.10)
project(RayTracer)

file(GLOB_RECURSE SOURCES
    "src/*.cc"
)

# for high performance
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ffast-math")
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

add_subdirectory(../cust-cpp-vector cust-vector_build)

find_package(OpenMP REQUIRED)

add_executable(ray-tracer ${SOURCES})

if(OpenMP_CXX_FOUND)
    target_link_libraries(ray-tracer PUBLIC OpenMP::OpenMP_CXX)
endif()

target_include_directories(ray-tracer PRIVATE
    "include"
)

target_link_libraries(ray-tracer PRIVATE CustVector)
