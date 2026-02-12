cmake_minimum_required(VERSION 3.10)
project(RayTracer)

add_subdirectory(../cust-cpp-vector cust-vector_build)

add_executable(ray-tracer src/main.cc)

target_include_directories(ray-tracer PRIVATE include)

target_link_libraries(ray-tracer PRIVATE CustVector)
