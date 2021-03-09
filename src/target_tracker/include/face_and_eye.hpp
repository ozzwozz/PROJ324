#ifndef FACE_AND_EYE_HPP
#define FACE_AND_EYE_HPP

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>

using namespace std;
using namespace cv;

class face_and_eye
{
  private:

    vector<Rect> foundLocations;
    vector<double> foundWeights;

  protected:
  public:
    face_and_eye()
    {
      HOGDescriptor hog; // creates the hog descriptor and detector
      hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
    }
    cv_bridge::CvImagePtr face_and_eye_rectangles(const cv_bridge::CvImagePtr frame); // function that marks face and eyes with rectangles
};

#endif
