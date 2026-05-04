cmake_minimum_required(VERSION 3.15)

project(SnakeQLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SnakeQLearning
        main.cpp
        Service.cpp Service.h
        QTable.cpp QTable.h
        Snake.cpp Snake.h
)

find_package(SFML 3 CONFIG REQUIRED COMPONENTS Graphics Window System)
target_link_libraries(SnakeQLearning PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
)