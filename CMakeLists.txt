cmake_minimum_required(VERSION 3.0.0)
project(CheckersCmake VERSION 0.1.0 )

include(CTest)
enable_testing()

add_subdirectory(thirdparty/catch)
add_subdirectory(thirdparty/sglib)
add_subdirectory(src)
add_subdirectory(test)
