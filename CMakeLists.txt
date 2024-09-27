cmake_minimum_required(VERSION 3.20)

# Project name
set(PROJECT_NAME "inkx")
project(${PROJECT_NAME})

# Compilation flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall  -Wpedantic -Wextra -pedantic-errors ")
if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
endif()

# Source files
set(SRC_FILES main.c ./data/gap_buffer/gap_buffer.c 
    ./data/text_struct/text_struct.c
	./data/dynamic_array/dynamicarray.c
    ./io/render_txt.c
    ./io/io.c
	ferror.c
)


find_package(Curses REQUIRED)

# Include the Curses library
include_directories(${CURSES_INCLUDE_DIR})

# Add the executable target and specify its source files
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link the ncurses library to the executable
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})

