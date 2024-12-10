cmake_minimum_required(VERSION 3.10)

project(Micrograd)

set(CMAKE_CXX_STANDARD 20)

# Add all .cpp files in the current directory and subdirectories
file(GLOB_RECURSE SRC_FILES "*.cpp")

# Exclude the build directory (if any)
list(FILTER SRC_FILES EXCLUDE REGEX "build/")

# Create executable
add_executable(main.out ${SRC_FILES})

# Link any libraries here (e.g., if you have any external dependencies)
# target_link_libraries(main.out <library_name>)
