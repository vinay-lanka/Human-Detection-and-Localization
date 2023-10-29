/**
 * @file detector_implementation.cpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief The file that fills in the stubs (empty placeholders) initialized in 'detector_header.hpp' with the actual methods.
 * @version 0.1
 * @date 2023-10-29
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "detector_header.hpp"

/**
 * @brief The constructor for the Detector class that initializes the YOLO v5 model, threshold values, and other instance member variables of the class.
 * 
 */
Detector::Detector(cv::dnn::Net yolo_model, int yolo_img_width, int yolo_img_height,
           float confidence_threshold, float nms_threshold, float score_threshold, int yolo_grid_cells, std::vector<std::string> yolo_classes): yolo_model{yolo_model}, yolo_img_size{cv::Size(yolo_img_width,yolo_img_height)},confidence_threshold{confidence_threshold},nms_threshold{nms_threshold},score_threshold{score_threshold},yolo_grid_cells{yolo_grid_cells},yolo_classes{yolo_classes}{
}

/**
 * @brief A function to preprocess the video frame (by resizing, reshaping, scaling, formatting, etc) before feeding it to YOLO v5.
 * 
 * @return * cv::Mat The 'blob' image ready to be fed to the YOLO v5 model
 */
cv::Mat Detector::preprocess_img(){
    cv::Mat blob ;
    float pixel_scaling = 1.0/255.0 ;
    cv::dnn::blobFromImage(img,blob,pixel_scaling,yolo_img_size,cv::Scalar(),true,false) ;
    return blob ;
}

/**
 * @brief A function to identify the true bounding boxes (using non-max suppression - NMS) and draw them on the video frame along with storing information of the bottom-middle pixel (necessary information for the Tracker) of each bounding box.
 * 
 * @param boxes Bounding box information (before NMS)
 * @param confidence_values Confidence value for each bounding box
 * @param box_pixels Bottom-middle pixel information for each bounding box (after NMS)
 * @return * void 
 */
void Detector::get_bounding_boxes(std::vector<cv::Rect> boxes, std::vector<float> confidence_values, std::vector<cv::Point> &box_pixels){
    std::vector<int> indices ;
    for(int i=0; i<boxes.size(); i++){
        cv::dnn::NMSBoxes(boxes,confidence_values,score_threshold,nms_threshold,indices);
    }
    for(int i=0; i<indices.size(); i++){
        cv::Rect current_box = boxes[indices[i]] ;
        int left = current_box.x, top = current_box.y, width = current_box.width, height = current_box.height ;
        rectangle(boxed_img,cv::Point(left,top),cv::Point(left+width,top+height),cv::Scalar(0, 0, 255),3);
        box_pixels.push_back(cv::Point(left + width/2, top + height)) ;
    }
}

/**
 * @brief A function to analyze the output of the YOLO v5 model run on the pre-processed video frame by identifying confidence and class scores along with bounding box and pixel information.
 * 
 * @param yolo_outputs The output vector of running the YOLO v5 model on the pre-processed video frame
 * @return * DetectorOutput The final output of the Detector object, ready to be given to the Tracker
 */
DetectorOutput Detector::postprocess_img(std::vector<cv::Mat> yolo_outputs){
    std::vector<int> classIDs ;
    std::vector<float> confidence_values ;
    std::vector<cv::Rect> boxes ;
    float x_scaling = (float)original_img_size.width/yolo_img_size.width ;
    float y_scaling = (float)original_img_size.height/yolo_img_size.height ;
    float *info = reinterpret_cast<float*>(yolo_outputs[0].data);
    for(int i=0; i<yolo_grid_cells; i++){
        float grid_cell_confidence = info[4] ;
        if(grid_cell_confidence > confidence_threshold){
            float person_class_score = info[5] ;
            cv::Mat class_scores_matrix(1,yolo_classes.size(),CV_32FC1,person_class_score) ;
            cv::Point classID ;
            double max_class_score ;
            minMaxLoc(class_scores_matrix,0,&max_class_score,0,&classID) ;
            if(max_class_score > score_threshold){
                confidence_values.push_back(grid_cell_confidence) ;
                classIDs.push_back(classID.x) ;
                float cx = info[0], cy = info[1], w = info[2], h = info[3] ;
                int left = static_cast<int>((cx - 0.5*w)*x_scaling) ;
                int top = static_cast<int>((cy - 0.5*h)*y_scaling) ;
                int width = static_cast<int>(w*x_scaling) ;
                int height = static_cast<int>(h*y_scaling) ;
                boxes.push_back(cv::Rect(left,top,width,height)) ;
            }
        }
        info += yolo_classes.size() + 5 ; ;
    }
    std::vector<cv::Point> box_pixels ;
    get_bounding_boxes(boxes,confidence_values,box_pixels) ;
    DetectorOutput final_answer ;
    final_answer.boxed_img = boxed_img ;
    final_answer.pixels = box_pixels ;
    return final_answer ;
}

/**
 * @brief A function that makes function calls to preprocess the video frame, run the YOLO model, and post-process the image.
 * 
 * @param video_frame The video frame from the camera of the system/robot
 * @return * DetectorOutput The final output of the Detector object, ready to be given to the Tracker
 */
DetectorOutput Detector::detect_humans(cv::Mat video_frame) {
    img = video_frame ;
    boxed_img = video_frame.clone() ;
    original_img_size = cv::Size(img.cols,img.rows) ;
    cv::Mat blob = preprocess_img() ;
    yolo_model.setInput(blob) ;
    std::vector<cv::Mat> yolo_outputs ;
    yolo_model.forward(yolo_outputs,yolo_model.getUnconnectedOutLayersNames()) ;
    DetectorOutput final_output = postprocess_img(yolo_outputs) ;
    return final_output ;
}

/**
 * @brief The destructor for the Detector class that deallocates any dynamically allocated memory for an object of the class.
 * 
 */
Detector::~Detector(){}