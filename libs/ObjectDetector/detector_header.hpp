/**
 * @file detector_header.hpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief The header file for the human obstacle detector with all the instance
 * member variables and functions.
 * @version 0.1
 * @date 2023-10-29
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#pragma once

/**
 * @brief A data structure for the Detector to return the exact information
 * required by the Tracker.
 *
 */
struct DetectorOutput {
  std::vector<cv::Point> pixels;
  cv::Mat boxed_img;
};

/**
 * @brief The Detector class that takes a video frame and returns the image with
 * bounding box drawn over it along with pixel information for the Tracker to
 * use.
 *
 */
class Detector {
 private:
  cv::dnn::Net yolo_model;
  cv::Size yolo_img_size;
  cv::Size original_img_size;
  const float confidence_threshold;
  const float nms_threshold;
  const float score_threshold;
  const int yolo_grid_cells;
  cv::Mat img;
  cv::Mat boxed_img;
  const std::vector<std::string> yolo_classes;
  cv::Mat preprocess_img();
  void get_bounding_boxes(std::vector<cv::Rect> boxes,
                          std::vector<float> confidence_values,
                          std::vector<cv::Point>& box_pixels);
  DetectorOutput postprocess_img(std::vector<cv::Mat> yolo_outputs);

 public:
  Detector(cv::dnn::Net yolo_model, int yolo_img_width, int yolo_img_height,
           float confidence_threshold, float nms_threshold,
           float score_threshold, int yolo_grid_cells,
           std::vector<std::string>& yolo_classes);
  DetectorOutput detect_humans(cv::Mat video_frame);
  ~Detector();
};