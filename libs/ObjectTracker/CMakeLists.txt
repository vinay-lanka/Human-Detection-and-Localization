find_package(OpenCV REQUIRED)

add_library(tracker_lib SHARED tracker_implementation.cpp)
target_include_directories(tracker_lib PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(tracker_lib
${OpenCV_LIBS}
)