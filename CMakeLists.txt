cmake_minimum_required(VERSION 3.0.0)
project(catmullrom VERSION 0.1.0)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

include(CTest)
enable_testing()

add_executable(catmullrom main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories(${EIGEN3_INCLUDE_DIR})
find_package(Python3 COMPONENTS Development NumPy)
target_include_directories(catmullrom PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
target_link_libraries(catmullrom Python3::Python Python3::NumPy)