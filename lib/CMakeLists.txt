project(CurvesLib)

# Create shared library
add_library(curves_lib SHARED 
    src/curves.cpp
)

target_include_directories(curves_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(curves_lib OpenMP::OpenMP_CXX)

# Install rules
install(TARGETS curves_lib
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/ DESTINATION include)
