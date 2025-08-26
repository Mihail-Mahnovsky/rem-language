cmake_minimum_required(VERSION 4.0)
project(remlang)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt.git
        GIT_TAG 11.2.0
)

fetchcontent_makeavailable(fmt)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
add_executable(remlang ${SOURCE_FILES})
target_link_libraries(remlang PRIVATE fmt::fmt)