/*
 *
 * References:
 * https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html
 */ 

#include <opencv2/highgui.hpp>
#include <opencv2/aruco_detector.hpp>
#include <opencv2/aruco/aruco_calib_pose.hpp>

#include <iostream>

#include "image_markers.hpp"

using namespace std;

using namespace cv;


int main( int argc, char* argv[] )
{
    // Capture video stream from the input argument device
    VideoCapture inputVideo;
    inputVideo.open(0);

    // Obtain ArUco dictionary and create detector
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_ARUCO_ORIGINAL);

    ImageMarkers marker_mngr(dictionary);

    while (inputVideo.grab()) {
        // Capture frame
        Mat image;
        inputVideo.retrieve(image);

        if (marker_mngr.detect(image)) {
            marker_mngr.draw(image);

            // Obtain and print markers in json
            string buff; 
            marker_mngr.get_json(buff);
            cout << "Markers found: " << endl << buff << endl;
        }

        // Show image
        imshow("out", image);
        char key = (char) waitKey(10);
        if (key == 27)
            break; 
    }
}