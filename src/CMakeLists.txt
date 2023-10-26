cmake_minimum_required(VERSION 3.26)
project(Project1_code)

set(CMAKE_CXX_STANDARD 14)

file(COPY classes_per_uc.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY classes.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY students_classes.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Project1_code
        teste.cpp
        Class.cpp
        UC.cpp
        Student.cpp
        Schedule.cpp)
