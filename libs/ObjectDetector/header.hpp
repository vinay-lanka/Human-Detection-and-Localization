#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>
#include <string>
#include <vector>

#pragma once

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