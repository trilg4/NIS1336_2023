cmake_minimum_required(VERSION 3.10.2)

project(ToDo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add include directory
include_directories(include)

# Add source files
set(SOURCES
    src/account.cpp
    src/task.cpp
    src/ui.cpp
    src/reminder.cpp
    main.cpp
)

# Create executable
add_executable(todo ${SOURCES})

# Set output directory for executable
set_target_properties(todo PROPERTIES RUNTIME_OUTPUT_DIRECTORY "build")

# Add data directory to output directory
add_custom_command(TARGET todo POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/bin/data)