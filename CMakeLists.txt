cmake_minimum_required(VERSION 3.15)
project(M4OEP)

set(CMAKE_CXX_STANDARD 17)

set(SFML_ROOT "C:/Users/Mitchell Steenbergen/SFML-2.6.1")
set(SFML_STATIC_LIBRARIES FALSE)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(M4OEP main.cpp
        Engine.cpp
        player.cpp
)
target_link_libraries(M4OEP sfml-graphics sfml-window sfml-system)