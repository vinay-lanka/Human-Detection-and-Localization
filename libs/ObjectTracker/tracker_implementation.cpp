/**
 * @file tracker_implementation.cpp
 * @author Vinay Lanka (vlanka@umd.edu)
 * @brief Implementation of the Geometric CV classes to convert pixels to
 * coordinates
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "tracker_header.hpp"
#include <cmath>
#include <string>

/**
 * @brief Construct a new Tracker:: Tracker object
 * 
 * @param height 
 * @param focal_length 
 * @param fov 
 * @param resolution 
 */

Tracker::Tracker(float height, float focal_length, float hfov, float vfov, std::vector<int> resolution, float pixel_size) {
  _height = height;
  _focal_length = focal_length;
  _hfov = hfov;
  _vfov = vfov;
  _resolution = resolution;
  _pixel_size = pixel_size;
}

/**
 * @brief Destroy the Tracker:: Tracker object
 * 
 */

Tracker::~Tracker(){}

/**
 * @brief Function to convert degrees to radians
 * 
 * @param deg 
 * @return float 
 */
float Tracker::degrees_to_radians(float deg) {
    return deg * M_PI / 180.0;
}

/**
 * @brief Function to convert radians to degrees
 * 
 * @param radians 
 * @return float 
 */
float Tracker::radians_to_degrees(float radians) {
    return radians * (180.0 / M_PI);
}

/**
 * @brief Convert pixels to the camera coordinate frame
 * 
 * @param prediction_pixels 
 * @return std::vector<std::vector<float>> 
 */

std::vector<std::vector<float>>  Tracker::pixel_to_camera_frame(std::vector<cv::Point> prediction_pixels) {
      std::vector<std::vector<float>> coordinates;
      for (auto & current_pixel : prediction_pixels){
        float offset_from_center = (current_pixel.y-((float)_resolution[1]/2)) * _pixel_size; //Converting pixel_offset to height in focal plane
        float dip_angle = (_vfov/2) - radians_to_degrees(std::atan2((offset_from_center),(_focal_length)));
        float z_min_plane = _height / tan(degrees_to_radians((_vfov/2)-dip_angle));
        float x_from_center = (current_pixel.x-640) * 2.8;

        float x_coord = x_from_center * z_min_plane / (_focal_length * 1000);
        coordinates.insert(coordinates.end(),{x_coord,_height, z_min_plane});
      }
  return coordinates;
}

/**
 * @brief Utility function to format strings
 * 
 * @tparam T 
 * @param a_value 
 * @param n 
 * @return std::string 
 */

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 6) {
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return std::move(out).str();
}

/**
 * @brief plot all the detected human coordinates on the given frame
 * 
 * @param coordinates 
 * @param frame 
 * @return cv::Mat 
 */
 
cv::Mat Tracker::plot_coordinates(std::vector<cv::Point>  prediction_pixels, std::vector<std::vector<float>> coordinates, cv::Mat frame){
   //Plot points on prediction
   for(int i = 0;i<prediction_pixels.size();i++){
    cv::Point pt = prediction_pixels[i];
    cv::circle(frame, pt, 1, cv::Scalar(0, 255, 0), 2, 8, 0);
    std::string text = to_string_with_precision(coordinates[i][0], 2) + "," + to_string_with_precision(coordinates[i][1],2) + "," + to_string_with_precision(coordinates[i][2],2);
    // cout << test[0][1];
    cv::putText(frame, text, pt, cv::FONT_HERSHEY_SIMPLEX , 1, {125, 246, 55}, 3);
   }
  return frame;
}