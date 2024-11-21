# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project ("Benchmarks")

# Include sub-projects.
add_subdirectory ("src/StringBenchmarks")
add_subdirectory ("src/CRTPBenchmarks")
