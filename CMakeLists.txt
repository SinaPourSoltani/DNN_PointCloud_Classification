cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(PointCloudManipulation)

set(CMAKE_CXX_STANDARD 17)

find_package( PCL 1.7 REQUIRED )

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable(playground playground.cpp)
add_executable(preprocess preprocessing.cpp)

target_link_libraries(playground ${PCL_LIBRARIES})
target_link_libraries(preprocess ${PCL_LIBRARIES})
