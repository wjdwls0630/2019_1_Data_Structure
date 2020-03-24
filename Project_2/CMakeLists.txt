#CMaeke powered build system for data structures.
#Create by JungJin Park
#First draft is 18. May. 2019


message("Using CMake version ${CMAKE_VERSION}")
message("Before 'project':")
message("  C: '${CMAKE_C_COMPILER}'")
message("  C++: '${CMAKE_CXX_COMPILER}'")
message("  Source: ${PROJECT_SOURCE_DIR}")
message("  Binary: ${PROJECT_BINARY_DIR}")
message("  Version: ${PROJECT_VERSION}")
message("  Version (alt): ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
cmake_minimum_required(VERSION 3.0)

project(My_Lab07 CXX )
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 1)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-g -o -Wall -std=c++17 ")
set ( CMAKE_EXE_LINKER_FLAGS "-Wl" )

set(SOURCE_FILES
        ./BaseApplication.cpp
        ./ItemType.cpp
        ./FolderType.cpp
        ./FileType.cpp
        ./TextFileType.cpp
        ./JPGFileType.cpp
        ./MP3FileType.cpp
        ./TextApplication.cpp
        ./JPGApplication.cpp
        ./main.cpp
        )

set(CMKAE_VERBOSE_MAKEFILE ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
add_executable(main ${SOURCE_FILES} )

target_link_libraries(main ${OpenCV_LIBS})
