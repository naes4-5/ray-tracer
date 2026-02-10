cmake_minimum_required(VERSION 3.10)
project(ray-tracer)

# 1. Bring in the library logic
add_subdirectory(../cust-cpp-vector cust-vector_build)

# 2. Create your app
add_executable(ray_tracer main.cc)

# 3. Link the interface
target_link_libraries(ray_tracer PRIVATE cust_vector_lib)
