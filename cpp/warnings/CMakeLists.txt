cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(warnings)

add_compile_options(
        -Wall
        -Wextra
        -Weffc++
        -Werror
        -Wuninitialized
        -Wreturn-type
        -Wconversion
        -Wsign-compare
        -Wunused-result
        -Wsuggest-override
        -Wzero-as-null-pointer-constant
        -Wmissing-declarations
        -Wold-style-cast
        -Wnon-virtual-dtor
)

file(GLOB SOURCES "*.cpp")
foreach (source ${SOURCES})
    get_filename_component(name ${source} NAME_WE)
    add_executable(${name} ${source})
endforeach()
