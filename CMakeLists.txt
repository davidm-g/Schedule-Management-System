cmake_minimum_required(VERSION 3.10)
project(manager)

set(CMAKE_CXX_STANDARD 14)

file(COPY src/classes_per_uc.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/classes.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY src/students_classes.csv DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(manager
        src/main.cpp
        src/Turma.cpp
        src/UC.cpp
        src/Student.cpp
        src/Schedule.cpp
        src/Menu.cpp
        src/Data.cpp
        src/Action.cpp
        src/Action.h
)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)