cmake_minimum_required(VERSION 3.20)

project(Rail)
set(CMAKE_CXX_STANDARD 20)
set(LLVM_DIR "C:/LLVM-21/lib/cmake/llvm")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
add_executable(railc Rail/main.cpp)

llvm_map_components_to_libnames(llvm_libs core support native)
target_link_libraries(railc ${llvm_libs})