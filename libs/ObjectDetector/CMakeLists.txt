find_package(OpenCV REQUIRED)

add_library(detector_lib SHARED implementation.cpp)
target_include_directories(detector_lib PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(detector_lib
${OpenCV_LIBS}
)