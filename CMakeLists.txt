cmake_minimum_required(VERSION 3.28)
project(cpp_game_of_life)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpp_game_of_life main.cpp include/conroy.cpp include/window.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR /sfml)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

target_link_libraries(cpp_game_of_life sfml-system sfml-window sfml-graphics sfml-audio)
