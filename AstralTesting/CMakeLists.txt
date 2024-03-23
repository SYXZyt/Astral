cmake_minimum_required(VERSION 3.2)

include_directories(../)
link_directories(.)

project(AstralOut)

set(CMAKE_CXX_STANDARD 17)

add_executable(AstralTesting Main.cpp)

if (UNIX)
    target_link_libraries(AstralTesting ${CMAKE_CURRENT_SOURCE_DIR}/libAstral.so)
elseif (WIN32)
    target_link_libraries(AstralTesting PUBLIC "Astral.lib")
endif()