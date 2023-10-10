cmake_minimum_required(VERSION 3.26)
project(Project1_code)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project1_code
        .idea/.gitignore
        .idea/modules.xml
        .idea/Project1_code.iml
        classes.csv
        classes_per_uc.csv
        students_classes.csv
        teste.cpp
        Class.h
        Class.cpp
        UC.h
        Parse_files.cpp)
