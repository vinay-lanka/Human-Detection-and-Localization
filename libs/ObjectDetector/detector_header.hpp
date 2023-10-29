/**
 * @file detector_header.hpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief This file contains the skeleton of the 'Detector' class which performs
 * human detection using YOLO v5 in HDAL.
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#pragma once

struct DetectorOutput{

  std::vector<cv::Point> pixels ;
  cv::Mat boxed_img ;

} ;

/**
 * @brief The 'Detector' class takes a video frame, preprocesses it, runs it
 * through YOLO v5, postprocesses it, and returns the final image and bounding
 * box information.
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
  cv::Mat img ;
  cv::Mat boxed_img ;
  std::vector<std::string> yolo_classes ;
  cv::Mat preprocess_img();
  void draw_bounding_boxes(std::vector<cv::Rect> boxes, std::vector<float> confidence_values) ;
  DetectorOutput postprocess_img(std::vector<cv::Mat> yolo_outputs);

 public:
  Detector(cv::dnn::Net yolo_model, int yolo_img_width, int yolo_img_height,
           float confidence_threshold, float nms_threshold, float score_threshold, int yolo_grid_cells,std::vector<std::string> yolo_classes);
  DetectorOutput detect_humans(cv::Mat video_frame);
  ~Detector();
};
