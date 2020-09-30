cmake_minimum_required(VERSION 3.8)

project(
        shakaembedded
    VERSION 0.1
    LANGUAGES C CXX     
)

add_executable(
    shakaembedded
    src/main.cpp
)

target_include_directories(
        shakaembedded
        PRIVATE thirdparty/include
)

add_library(shaka-player-embedded SHARED IMPORTED)
add_library(shaka-player-embedded.ffmpeg SHARED IMPORTED)

set_target_properties( shaka-player-embedded PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/lib/libshaka-player-embedded.so)
set_target_properties( shaka-player-embedded.ffmpeg PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/thirdparty/lib/libshaka-player-embedded.ffmpeg.so)
target_link_libraries( shakaembedded shaka-player-embedded shaka-player-embedded.ffmpeg)

set_target_properties(
        shakaembedded
        PROPERTIES CXX_STANDARD 11
)
