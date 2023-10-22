#include "header.hpp"

Detector::Detector(std::string yolo_model_path, cv::Size yolo_img_size, float confidence_threshold, float iou_threshold){

}

void Detector::preprocess_img(cv::Mat &img){

}

std::vector<float> Detector::postprocess_img(std::vector<Ort::Value> model_output){
    std::vector<float> temp ;
    return temp ;
}

std::vector<float> Detector::detect_humans(cv::Mat &img){
    std::vector<float> temp ;
    return temp ;
}

Detector::~Detector(){
    
}