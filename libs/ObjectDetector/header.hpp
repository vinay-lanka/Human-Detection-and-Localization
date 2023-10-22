/**
 * @file header.hpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief This file contains the skeleton of the 'Detector' class which performs human detection using YOLO v5 in HDAL.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
#include <string>
#include <vector>

#pragma once

/**
 * @brief The 'Detector' class takes a video frame, preprocesses it, runs it through YOLO v5, postprocesses it, and returns the final image and bounding box information.
 * 
 */
class Detector{

    private:
        std::string yolo_model_path ;
        cv::Size yolo_img_size ;
        cv::Size original_img_size ;
        float confidence_threshold ;
        float iou_threshold ;
        std::vector<int> input_tesor_shape ;
        std::vector<int> output_tensor_shape ;
        std::vector<int> resized_img_shape ;
        std::vector<std::string> ort_input_names ;
        std::vector<std::string> ort_output_names ;
        Ort::Env env ;
        Ort::SessionOptions sessionoptions ;
        Ort::Session session ;
        void preprocess_img(cv::Mat &img) ;
        std::vector<float> postprocess_img(std::vector<Ort::Value> model_output) ;
    public:
        Detector(std::string yolo_model_path, cv::Size yolo_img_size, float confidence_threshold, float iou_threshold) ;
        std::vector<float> detect_humans(cv::Mat &img) ;
        ~Detector() ;

} ;