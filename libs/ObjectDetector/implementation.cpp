/**
 * @file implementation.cpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief This file contains the implementations for each of the instace member functions of the 'Detector' class of HDAL's human detector.
 * @version 0.1
 * @date 2023-10-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "header.hpp"

/**
 * @brief The constructor of 'Detector' that initializes ONNX (ORT) runtime and other system variables.
 * 
 */
Detector::Detector(std::string yolo_model_path, cv::Size yolo_img_size, float confidence_threshold, float iou_threshold){

}

/**
 * @brief The function that preprocesses (resizes, reshapes, changes the format, changes the data type, etc) the video frame before running it through YOLO v5. 
 * 
 * @param img The video frame
 * @return * void 
 */
void Detector::preprocess_img(cv::Mat &img){

}

/**
 * @brief The function that postprocesses (analyze output tensor, draw bounding boxes, etc) the image (video frame) after running it through YOLO v5.
 * 
 * @param model_output The output tensor on running the video frame through YOLO v5.
 * @return * std::vector<float> The detection information (confidences, positions, bounding boxes, etc)
 */
std::vector<float> Detector::postprocess_img(std::vector<Ort::Value> model_output){
    std::vector<float> temp ;
    return temp ;
}

/**
 * @brief The wrapper function that calls the preprocessing method, runs the YOLO v5 model on the image, calls the postprocessing method, and returms the information that is to be fed to the object tracker.
 * 
 * @param img The video frame that is to be preprocessed
 * @return * std::vector<float> The final detection information that is to be fed to the object tracker
 */
std::vector<float> Detector::detect_humans(cv::Mat &img){
    std::vector<float> temp ;
    return temp ;
}

/**
 * @brief The destructor for the 'Detector' class that deallocates any dynamically created memory.
 * 
 */
Detector::~Detector(){

}