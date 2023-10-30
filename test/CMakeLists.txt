add_executable(cpp-test main.cpp test.cpp)
target_link_libraries(cpp-test PUBLIC gtest gmock detector_lib tracker_lib)
gtest_discover_tests(cpp-test)