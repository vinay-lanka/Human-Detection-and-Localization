/**
 * @file tracker_header.hpp
 * @author Vinay Lanka (vlanka@umd.edu)
 * @brief Header definitions of the Geometric CV classes to convert pixels to coordinates
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <vector>

#pragma once

class Tracker{
    private:
        Eigen::Matrix<float, 3, 4> camera_matrix;
        Eigen::VectorXd pixel_coordinates[2];
        Eigen::Vector3d real_world_coordinates;
        float height;
        float focal_length;
        int fov;
        std::vector<std::vector<int>> resolution;
        std::vector<std::vector<int>> prediction_pixels;
    public:
        Eigen::VectorXd pixel_to_camera_frame(std::vector<std::vector<int>> prediction_pixels);
        Tracker(float height, float focal_length, int fov, std::vector<std::vector<int>> resolution);
        ~Tracker();
};