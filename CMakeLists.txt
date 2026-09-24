cmake_minimum_required(VERSION 3.10)
project(MyProject)
find_package(OpenCV REQUIRED)
add_executable(MyProject src/main.cpp src/camera.cpp src/detector.cpp)
target_include_directories(MyProject PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(MyProject ${OpenCV_LIBS})

