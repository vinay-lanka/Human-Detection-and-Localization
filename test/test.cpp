/**
 * @file test.cpp
 * @author Vinay Lanka (vlanka@umd.edu)
 * @brief Tests for the Human Tracker Implementation
 * @version 0.1
 * @date 2023-10-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <gtest/gtest.h>

#include <vector>

#include <opencv2/core/mat.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include "detector_header.hpp"
#include "tracker_header.hpp"

/**
 * @brief Testing to check if base tests work.
 *
 */
TEST(dummy_test, pass_test) { EXPECT_EQ(1, 1); }

TEST(DetectorTest, test_constructor) {
  cv::Mat M(102, 201, CV_8UC1);
  int rows = M.rows;
  int cols = M.cols;
  cv::Size test_size = M.size();
  Detector test_detector("path", test_size, 100.0, 100.0);
}

TEST(DetectorTest, test_detection) {
  cv::Mat M(102, 201, CV_8UC1);
  int rows = M.rows;
  int cols = M.cols;
  cv::Size test_size = M.size();
  Detector test_detector("path", test_size, 100.0, 100.0);
  std::vector<float> result = test_detector.detect_humans(M);
  std::vector<float> test = {-1.0};
  ASSERT_EQ(test, result);
}

TEST(TrackerTest, test_constructor) {
  std::vector<std::vector<int>> test_resolution = {{1, 1}};
  Tracker test_tracker(100.0, 100.0, 45, test_resolution);
}

TEST(TrackerTest, test_pixel_to_camera_frame) {
  std::vector<std::vector<int>> test_resolution = {{1, 1}};
  Tracker test_tracker(100.0, 100.0, 45, test_resolution);
  Eigen::VectorXd test_result(2);
  test_result[0] = -1;
  test_result[1] = -1;
  std::vector<std::vector<int>> test_prediction = {{1, 1}};
  Eigen::VectorXd test_vector =
      test_tracker.pixel_to_camera_frame(test_prediction);
  ASSERT_EQ(test_vector, test_result);
}
