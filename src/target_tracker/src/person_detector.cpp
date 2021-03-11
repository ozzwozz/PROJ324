#include "person_detector.hpp"

cv::Mat person_detector::person_tracker(cv::Mat Frame)
{
  boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
  cv::HOGDescriptor hog;
  hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
  _hogCPU.reset( new cv::HOGDescriptor );
  _hogCPU->setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector() );

  //cv::HOGDescriptor hog;
  hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());

  //CRASHES


  cv::cvtColor(Frame, greyFrame, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(greyFrame, greyEqFrame);


  //CRASHES


  std::vector<cv::Rect> foundLocations;


  int minNeighbours = 1;
  int flags = 0;

  hog.detectMultiScale(Frame, foundLocations);

  for (size_t i = 0; i < foundLocations.size(); i++)
  {
    cv::Rect r = foundLocations[i];
    rectangle(Frame, foundLocations[i], cv::Scalar(0, 0, 255), 3);
  }

  std::vector<cv::Rect> detections;

  //detectPersons(Frame, detections);

  if ( _imageScaling != 1.0 )
  {
    //scaleDetections(detections,1,1);
  }
  return Frame;
}


void person_detector::scaleDetections(std::vector<cv::Rect>& detections, double scaleX, double scaleY) const
{
  BOOST_FOREACH(cv::Rect& detection, detections)
  {
    cv::Rect roi(detection);
    detection.x      = static_cast<long>(roi.x      * scaleX);
    detection.y      = static_cast<long>(roi.y      * scaleY);
    detection.width  = static_cast<long>(roi.width  * scaleX);
    detection.height = static_cast<long>(roi.height * scaleY);
  }
}

void person_detector::detectPersons(const cv::Mat& img,std::vector<cv::Rect>& detections)
{
  double start = static_cast<double>(cv::getTickCount());

  // _hogCPU->detectMultiScale(img,
  //                           detections,
  //                           0,                //hit threshold: decrease in order to increase number of detections but also false alarms
  //                           cv::Size(8,8),    //win stride
  //                           cv::Size(0,0),    //padding 24,16
  //                           1.02,             //scaling
  //                           1,                //final threshold
  //                           false);            //use mean-shift to fuse detections

  double stop = static_cast<double>(cv::getTickCount());
  ROS_DEBUG_STREAM("Elapsed time in detectMultiScale: " << 1000.0*(stop-start)/cv::getTickFrequency() << " ms");
}
