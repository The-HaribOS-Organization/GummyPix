cmake_minimum_required(VERSION 3.25)

project(GummyPixLib VERSION 1.0 DESCRIPTION "Image processing library")
add_library(GummyPixLib SHARED
    src/format/bitmap.c
    src/image.c
    src/shape.c
    src/convolution.c
)

find_package(OpenMP REQUIRED)
target_link_libraries(
    GummyPixLib
    m
    OpenMP::OpenMP_C
)

target_include_directories(GummyPixLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS GummyPixLib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include/GummyPix)
