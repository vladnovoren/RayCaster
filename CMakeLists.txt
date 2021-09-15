cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(RayCaster VERSION 1.0)

set(FLAGS "-Wall -Wextra -g -O3")
set(CMAKE_CXX_FLAGS ${FLAGS})

add_executable(ray_caster src/main.cpp src/ray_caster.cpp src/quad.cpp src/geometry.cpp src/app.cpp src/world.cpp src/color.cpp src/button.cpp)
add_executable(test_vec src/test_vec.cpp src/geometry.cpp src/color.cpp src/quad.cpp)

target_include_directories(ray_caster PUBLIC include/)
target_include_directories(test_vec PUBLIC include/)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

target_link_libraries(ray_caster ${SDL2_LIBRARIES})
