cmake_minimum_required(VERSION 3.0.0)
project(VertexUI VERSION 0.1.0)

include(CTest)
enable_testing()

AUX_SOURCE_DIRECTORY(. SRC_LIST) #将./下的所有*.cpp加入到SRC_LIST中
add_library(VertexUI ${SRC_LIST})
target_precompile_headers(${PROJECT_NAME}
    PUBLIC
    framework.h})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
