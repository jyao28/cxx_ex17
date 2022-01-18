cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


include(CTest)
enable_testing()

FILE (GLOB USER_SRC ${CMAKE_SOURCE_DIR}/*.c ${CMAKE_SOURCE_DIR}/*.cpp)

add_executable(ex2 ${USER_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
