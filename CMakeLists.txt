cmake_minimum_required(VERSION 3.10)

# Set the project name
project(MyCProject)

# Add the 'googletest' subdirectory to your project
add_subdirectory(googletest)

# Add your own source files here (e.g., main.c)
add_executable(MyExecutable src/main.c)

# Link against Google Test
target_link_libraries(MyExecutable gtest_main stdc++fs)

# Add the 'tests' subdirectory to your project
add_subdirectory(tests)
