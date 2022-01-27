cmake_minimum_required(VERSION 3.21)
project(krpsim)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        main.cpp
        Process.cpp
        Resource.cpp
        Graph.cpp
        GraphCalculator.cpp
        parse/Grammar.yy.cpp
        parse/Lexer.ll.cpp
        parse/ParseProcess.cpp
        parse/ParseProcess.hpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        utilities
        parse
        .
        )

INCLUDE(ParseGenerator.cmake)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
