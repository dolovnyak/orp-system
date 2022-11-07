cmake_minimum_required(VERSION 3.21)
project(krpsim)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/Process.cpp
        src/Resource.cpp
        src/Graph.cpp
        src/GraphCalculator.cpp
        src/parse/Grammar.yy.cpp
        src/parse/Lexer.ll.cpp
        src/parse/ParseProcess.cpp
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        src/utilities
        src/parse
        src
        )

INCLUDE(ParseGenerator.cmake)

# replaced executable file to root dir
set_target_properties(${PROJECT_NAME}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )

#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
