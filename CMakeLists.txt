cmake_minimum_required(VERSION 3.31)
project(project_oop)

set(CMAKE_CXX_STANDARD 20)

add_executable(project_oop main.cpp
        rooms/Room.h
        rooms/SingleRoom.cpp
        rooms/SingleRoom.h)
