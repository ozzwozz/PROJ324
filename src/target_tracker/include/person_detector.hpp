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
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

// Boost headers
#include <boost/scoped_ptr.hpp>
#include <boost/foreach.hpp>

// Std C++ headers
#include <vector>

class person_detector
{
  private:
    //std::vector<cv::Rect> found;
    std::vector<double> weights;
    cv::Mat shirtColour(cv::Mat Frame);
    cv::Rect rectangleCheck(cv::Mat Frame, std::vector<cv::Rect> foundLocations);
    cv::Mat imageOverlay(cv::Mat WorkingFrame, cv::Mat FilteredFrame, cv::Mat OriginalFrame);
    cv::Rect pixelcount(cv::Mat FilteredFrame, std::vector<cv::Rect> foundLocations);
    cv::Point GetTargetCenter(cv::Rect Target_Box);
    cv::Mat MovementLine(std::vector<cv::Point> target_center, cv::Mat CurrentFrame, cv::Scalar LineColour);
    std::vector<cv::Point> CalculateRateOfMovement(std::vector<cv::Point> KnownPoints /*Timestamp for points*/);
    std::vector<cv::Point> MakeEstimation(std::vector<cv::Point> relative_movement, cv::Point LastPrecise);


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

  protected:
    ros::Time _imgTimeStamp;
    //boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
    double _imageScaling;

    //cv::HOGDescriptor hog;
};
#endif
