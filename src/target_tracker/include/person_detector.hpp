#ifndef PERSON_DETCTOR_HPP
#define PERSON_DETCTOR_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv_modules.hpp>
#include <opencv2/face.hpp>
#include <opencv2/dnn/dnn.hpp>
#include <opencv2/opencv.hpp>
#include <ros/ros.h>

// Boost headers
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>

// Std C++ headers
#include <vector>

class person_detector
{
  private:
    cv::Mat greyFrame;
    cv::Mat greyEqFrame;
    //std::vector<cv::Rect> found;
    std::vector<double> weights;
  public:
    //constructor
    person_detector()
    {
      // // cv::HOGDescriptor hog;
      // // hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
      // _hogCPU.reset( new cv::HOGDescriptor );
      // _hogCPU->setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector() );
    }
    //destructor
    ~person_detector()
    {

    }
    cv::Mat person_tracker(cv::Mat Frame);

    void detectPersons(const cv::Mat& img,
                     std::vector<cv::Rect>& detections);

  void scaleDetections(std::vector<cv::Rect>& detections,
                       double scaleX, double scaleY) const;
  protected:
    ros::Time _imgTimeStamp;
    //boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
    double _imageScaling;

    //cv::HOGDescriptor hog;
};
#endif
