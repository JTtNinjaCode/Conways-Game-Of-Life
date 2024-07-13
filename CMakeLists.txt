cmake_minimum_required(VERSION 3.0)

set (CMAKE_CXX_STANDARD 17)
project(conways_game_of_life)

add_subdirectory(third_party)

set(SRC_DIR ./src/)
add_executable(conways_game_of_life
    "${SRC_DIR}/main.cpp"
    "${SRC_DIR}/pattern.cpp"
    "${SRC_DIR}/game_context.cpp"
)
find_package(OpenGL REQUIRED)
target_link_libraries(conways_game_of_life glfw imgui OpenGL::GL glad)
