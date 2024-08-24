cmake_minimum_required(VERSION 3.22)

project(foundation LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(TBB REQUIRED)
if (TBB_FOUND)
    message(STATUS "TBB found")
else ()
    message(FATAL_ERROR "TBB not found")
endif ()

#add_subdirectory(cpp/pmr)
add_subdirectory(cpp/error_code)