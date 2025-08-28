cmake_minimum_required(VERSION 4.0)
project(remlang)

set(CMAKE_CXX_STANDARD 26)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
add_executable(remlang ${SOURCE_FILES}
        source/parser/types.hpp
        source/parser/ast/Context.cpp
        source/parser/ast/Context.hpp
        source/parser/ast/StringLiteral.hpp
        source/parser/ast/BoolLiteral.hpp
        source/parser/ast/UnaryNode.hpp
        source/parser/ast/IfNode.cpp
        source/parser/ast/IfNode.hpp
        source/parser/ast/while.hpp
        source/parser/ast/while.cpp
)