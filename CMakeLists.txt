cmake_minimum_required(VERSION 3.10)
project(ProjectileTracker)
 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
find_package(OpenCV REQUIRED)
 
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
 
add_executable(ProjectileTracker
    src/main.cpp
    src/camera.cpp
    src/detector.cpp
    src/tracker.cpp
    src/trajectory.cpp
)
 
target_link_libraries(ProjectileTracker ${OpenCV_LIBS})

