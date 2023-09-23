cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyProject)

# Add the 'googletest' subdirectory to your project
add_subdirectory(googletest)

# Add your own source files here
add_executable(MyExecutable src/main.c)

# Link against Google Test
target_link_libraries(MyExecutable gtest gtest_main)

# Add the 'tests' subdirectory to your project
add_subdirectory(tests)
