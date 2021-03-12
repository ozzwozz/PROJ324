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

  //cv::cvtColor(Frame, greyFrame, cv::COLOR_BGR2GRAY);
  //cv::equalizeHist(greyFrame, greyEqFrame);

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

  cv::Point target_center = shirtColour(Frame);


  cv::circle(Frame, cv::Point(target_center), 10, CV_RGB(255,255,255), 5);


  return Frame;
}

cv::Point person_detector::shirtColour(cv::Mat Frame)
{
  cv::Mat HSVFrame;
  cv::Mat FilteredFrame;
  cv::cvtColor(Frame, HSVFrame, cv::COLOR_BGR2HSV);
  //isolate red colours in Frame to find targets T-shirt
  // defined Hue, Saturation, Value
  cv::inRange(HSVFrame, (130, 70, 70), (160, 100, 100), FilteredFrame);
  //use to find center of red mass
  cv::Moments m = cv::moments(FilteredFrame, true);
  cv::Point target_center(m.m10/m.m00, m.m01/m.m00);
  return target_center;
}
