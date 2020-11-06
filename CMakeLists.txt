cmake_minimum_required(VERSION 3.5)

project(OSG_static_example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern)

add_executable(OSG_static_example main.cpp)

target_link_libraries(OSG_static_example
    osgdb_openflight
    osgdb_rgb
    osgdb_png
    osgdb_jpeg
    osgdb_zip
    osgDB
    osg
)

target_include_directories(OSG_static_example PRIVATE ${osg_INCLUDE_DIRS})
