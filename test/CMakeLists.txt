add_executable(cpp-test main.cpp test.cpp)
target_link_libraries(cpp-test PUBLIC gtest detector_lib tracker_lib)
gtest_discover_tests(cpp-test)