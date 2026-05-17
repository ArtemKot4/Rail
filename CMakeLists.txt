cmake_minimum_required(VERSION 3.20)
project(Rail)

set(CMAKE_CXX_STANDARD 20)

set(LLVM_DIR "C:/LLVM-21/lib/cmake/llvm")

find_package(LLVM REQUIRED CONFIG)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
add_executable(railc ${SOURCES})

target_include_directories(railc PRIVATE 
    ${LLVM_INCLUDE_DIRS}
    "src"
)

llvm_map_components_to_libnames(llvm_libs core support native)
target_link_libraries(railc ${llvm_libs})