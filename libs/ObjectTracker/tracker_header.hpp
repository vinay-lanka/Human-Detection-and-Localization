/**
 * @file tracker_header.hpp
 * @author Vinay Lanka (vlanka@umd.edu)
 * @brief Header definitions of the Geometric CV classes to convert pixels to
 * coordinates
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <opencv2/opencv.hpp>
#include <vector>

#pragma once

/**
 * @brief Tracker class that converts prediction_pixels to the camera coordinate frame
 * 
 */

class Tracker {
 private:
  float _height;
  float _focal_length;
  float _hfov;
  float _vfov;
  float _pixel_size;
  std::vector<int> _resolution;
  float degrees_to_radians(float);
  float radians_to_degrees(float radians);
 public:
  std::vector<std::vector<float>> pixel_to_camera_frame(std::vector<cv::Point> prediction_pixels);
  cv::Mat plot_coordinates(std::vector<cv::Point>  prediction_pixels, std::vector<std::vector<float>> coordinates, cv::Mat frame);
  Tracker(float height, float focal_length, float hfov, float vfov,std::vector<int> resolution, float pixel_size);
  ~Tracker();
};
