cmake_minimum_required(VERSION 3.20)
project(rtl_scanner LANGUAGES CXX)

add_executable(scanner)
target_sources(scanner PRIVATE "scanner.cpp")

target_include_directories(scanner PRIVATE "${PROJECT_SOURCE_DIR}")
add_subdirectory("rtl_proxy")
add_subdirectory("signal_processor")


find_package(Armadillo REQUIRED)  # Find Armadillo (report error if not found)
include_directories(${ARMADILLO_INCLUDE_DIRS})  # Add Armadillo include paths
target_link_libraries(scanner ${ARMADILLO_LIBRARIES})  # Link against Armadillo libraries

install(TARGETS scanner)