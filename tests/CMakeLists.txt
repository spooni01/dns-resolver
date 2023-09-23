add_executable(runTests tests_parameters.c)
target_link_libraries(runTests gtest gtest_main)

# Optionally, link against your main project if needed
target_link_libraries(runTests MyExecutable)
