
#include <iostream>
#include <fstream>
#include "detector_header.hpp"
#include "tracker_header.hpp"

const std::string CLASSLIST_PATH = "../data/coco.names" ;
const std::string MODEL_PATH = "../model/yolov5s.onnx" ;

const float YOLO_IMG_WIDTH = 640.0 ;
const float YOLO_IMG_HEIGHT = 640.0 ;

const float CONFIDENCE_THRESHOLD = 0.45 ;
const float NMS_THRESHOLD = 0.45 ;
const float SCORE_THRESHOLD = 0.45 ;
const int YOLO_GRID_CELLS = 25200 ;

int main(){

    std::vector<std::string> yolo_classes;
    std::ifstream read_input(CLASSLIST_PATH);
    std::string text;
    while (read_input >> text) {
        getline(read_input, text);
        yolo_classes.push_back(text) ;
    }
    cv::VideoCapture capture_frame(0);
    cv::Mat video_frame;
    cv::dnn::Net yolo_model = cv::dnn::readNet(MODEL_PATH) ;
    Detector detector(yolo_model,YOLO_IMG_WIDTH,YOLO_IMG_HEIGHT,CONFIDENCE_THRESHOLD,NMS_THRESHOLD,SCORE_THRESHOLD,YOLO_GRID_CELLS,yolo_classes) ;
    while(1){
        capture_frame.read(video_frame);
        DetectorOutput output = detector.detect_humans(video_frame) ;
        cv::imshow("Output Image",output.boxed_img) ;
        cv::waitKey(1);
    }
    return 0;

}
