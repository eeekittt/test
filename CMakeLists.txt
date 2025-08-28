cmake_minimum_required(VERSION 3.12)
project(CurvesProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable OpenMP
find_package(OpenMP REQUIRED)

add_subdirectory(lib)
add_subdirectory(app)