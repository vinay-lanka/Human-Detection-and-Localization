/**
 * @file implementation.cpp
 * @author Vinay Lanka (vlanka@umd.edu)
 * @brief Implementation of the Geometric CV classes to convert pixels to coordinates
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "header.hpp"

Tracker::Tracker(float height, float focal_length, int fov, std::vector<std::vector<int>> resolution){
}

Tracker::~Tracker(){
}

Eigen::VectorXd Tracker::pixel_to_camera_frame(std::vector<std::vector<int>> prediction_pixels){
Eigen::VectorXd var(2);
var[0] = -1;
var[1] = -1;
return var;
}
