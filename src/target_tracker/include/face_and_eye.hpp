#ifndef FACE_AND_EYE_HPP
#define FACE_AND_EYE_HPP

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <ros/ros.h>
#include <image_transport/image_transport.h>

using namespace std;
using namespace cv;

class face_and_eye
{
  private:

    vector<Rect> foundLocations;
    vector<double> foundWeights;
    //HOGDescriptor hog; // creates the hog descriptor and detector
    cv::CascadeClassifier hog; // creates the hog descriptor and detector
  protected:
  public:
    face_and_eye()
    {

      //hog.winSize = wsize;

      //hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    }
    cv::Mat face_and_eye_rectangles(cv::Mat frame); // function that marks face and eyes with rectangles
};

#endif
