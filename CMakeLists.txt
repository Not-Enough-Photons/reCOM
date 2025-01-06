cmake_minimum_required(VERSION 2.8)

project(gamez)
set(CMAKE_CXX_STANDARD 17)

set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(FTS_APP_DIR "${PROJECT_SOURCE_DIR}/Apps/FTS")

file(GLOB_RECURSE IMPL_FILES CMAKE_CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE HEADER_FILES CMAKE_CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.h")

add_executable(gamez "${FTS_APP_DIR}/main.cpp")

target_include_directories(gamez PUBLIC HEADER_FILES)
target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm glfw glad stb_image)