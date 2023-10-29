/**
 * @file main.cpp
 * @author Vikram Setty (vikrams@umd.edu)
 * @brief A file that does a demo run of the project by performing HDAL using
 * the system webcam.
 * @version 0.1
 * @date 2023-10-22
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "detector_header.hpp"
#include "tracker_header.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

using namespace std;

/**
 * @brief The code for this demo file is all embedded only in the 'main'
 * function.
 *
 * @return * int
 */

int main() { 
    //Initialise Camera
    cv::VideoCapture cap("/dev/video0");
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT,720);
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    //Parameters to initialise tracker object
    float height = 0.762;
    float focal_length = 1.898;
    float hfov = 100.11;
    float vfov = 56.34;
    float pixel_size = 0.0028;
    std::vector<int> resolution = {1280,720};
    //Create tracker object
    Tracker *human_tracker = new Tracker(height, focal_length, hfov, vfov, resolution, pixel_size);
    while(1){
        cv::Mat frame;
        cap >> frame;
        // If the frame is empty, break immediately
        if (frame.empty())
            break;
        //Detector method comes here to populate prediction pixels
        std::vector<std::vector<int>> prediction_pixels = {{0,540},{640,540}};
        //Calling tracker method for coordinates in camera frame
        std::vector<std::vector<float>> coordinates = human_tracker->pixel_to_camera_frame(prediction_pixels);
        //Plot coordinates on frame
        cv::Mat final_frame = human_tracker->plot_coordinates(prediction_pixels, coordinates, frame);
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
