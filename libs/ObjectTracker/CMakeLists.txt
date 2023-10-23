find_package(OpenCV REQUIRED)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


add_library(tracker_lib SHARED tracker_implementation.cpp)
target_include_directories(tracker_lib PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(tracker_lib
Eigen3::Eigen
${OpenCV_LIBS}
)