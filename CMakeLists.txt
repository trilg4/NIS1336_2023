cmake_minimum_required(VERSION 3.10.2)

project(todo)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find the required libraries
find_package(OpenSSL REQUIRED)

# Add the include directories for OpenSSL
include_directories(${OPENSSL_INCLUDE_DIR})

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

# Link against the OpenSSL library
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)