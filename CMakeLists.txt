cmake_minimum_required(VERSION 3.26)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio)

#add_executable(tron menu.cpp)
add_executable(tron main.cpp Header.h Player.h)

target_link_libraries(tron sfml-graphics sfml-audio)