add_executable(HDAL_demo main.cpp)
find_package(OpenCV REQUIRED)

target_include_directories(HDAL_demo PUBLIC 
${OpenCV_INCLUDE_DIRS}
.)

target_link_libraries(HDAL_demo PUBLIC detector_lib tracker_lib ${OpenCV_LIBS})