cmake_minimum_required(VERSION 3.0.0)
project(VertexUI-TEST VERSION 0.1.0)

include(CTest)
enable_testing()
add_subdirectory(..)
include_directories(../VertexUI)
add_library(${PROJECT_NAME} main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
