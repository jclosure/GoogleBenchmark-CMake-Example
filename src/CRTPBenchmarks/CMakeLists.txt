# CMakeList.txt : CMake project for StringBenchmarks, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.11)

# Include Google Benchmark
include(../cmake/GoogleBenchmark.cmake)

# Add source to this project's executable.
file(GLOB_RECURSE HEADERS *.h *.hpp)
file(GLOB_RECURSE SOURCES *.cc *.cpp)
add_executable (CRTPBenchmarks ${HEADERS} ${SOURCES})


# Link Google Benchmark to the project
target_link_libraries(CRTPBenchmarks benchmark::benchmark)

# Link Shlwapi to the project
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
    target_link_libraries(CRTPBenchmarks Shlwapi)
endif()

# TODO: Add tests and install targets if needed.
