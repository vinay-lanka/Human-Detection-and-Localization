
#include <iostream>
#include <fstream>
#include "detector_header.hpp"
#include "tracker_header.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace std;


//Parameters to initialise detector object
const std::string CLASSLIST_PATH = "../data/coco.names" ;
const std::string MODEL_PATH = "../model/yolov5s.onnx" ;

const float YOLO_IMG_WIDTH = 640.0 ;
const float YOLO_IMG_HEIGHT = 640.0 ;

const float CONFIDENCE_THRESHOLD = 0.45 ;
const float NMS_THRESHOLD = 0.45 ;
const float SCORE_THRESHOLD = 0.5 ;
const int YOLO_GRID_CELLS = 25200 ;

//Parameters to initialise tracker object
const float HEIGHT = 0.762;
const float FOCAL_LENGTH = 1.898;
const float HFOV = 100.11;
const float VFOV = 56.34;
const float PIXEL_SIZE = 0.0028;
const std::vector<int> RESOLUTION = {1280,720};

/**
 * @brief The code for this demo file is all embedded only in the 'main'
 * function.
 *
 * @return * int
 */

int main() { 
    std::vector<std::string> yolo_classes;
    std::ifstream read_input(CLASSLIST_PATH);
    std::string text;
    while (read_input >> text) {
        getline(read_input, text);
        yolo_classes.push_back(text) ;
    }
    cv::dnn::Net yolo_model = cv::dnn::readNet(MODEL_PATH) ;
    Detector detector(yolo_model,YOLO_IMG_WIDTH,YOLO_IMG_HEIGHT,CONFIDENCE_THRESHOLD,NMS_THRESHOLD,SCORE_THRESHOLD,YOLO_GRID_CELLS,yolo_classes) ;
    //Initialise Camera
    cv::VideoCapture cap("/dev/video0");
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    //Create tracker object
    Tracker *human_tracker = new Tracker(HEIGHT, FOCAL_LENGTH, HFOV, VFOV, RESOLUTION, PIXEL_SIZE);
    while(1){
        cv::Mat frame;
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
            break;

        DetectorOutput output = detector.detect_humans(frame) ;
        //Detector method comes here to populate prediction pixels
        std::vector<cv::Point> prediction_pixels = output.pixels;
        //Calling tracker method for coordinates in camera frame
        std::vector<std::vector<float>> coordinates = human_tracker->pixel_to_camera_frame(prediction_pixels);
        //Plot coordinates on frame
        cv::Mat final_frame = human_tracker->plot_coordinates(prediction_pixels, coordinates, output.boxed_img);
        //Display the frame
        cv::imshow( "Frame", final_frame );
        char c=(char)cv::waitKey(25);
        if(c==27)
            break;
    }
    // Close capture object
    cap.release();
    // Closes all the frames
    cv::destroyAllWindows();
    return 0; 

}
