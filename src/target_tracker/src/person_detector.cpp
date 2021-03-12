#include "person_detector.hpp"

cv::Mat person_detector::person_tracker(cv::Mat Frame)
{
  boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
  cv::HOGDescriptor hog;

  //re-trains the network every frame
  hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
  _hogCPU.reset( new cv::HOGDescriptor );
  _hogCPU->setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector() );

  //CRASHES

  //cv::cvtColor(Frame, greyFrame, cv::COLOR_BGR2GRAY);
  //cv::equalizeHist(greyFrame, greyEqFrame);

  //CRASHES


  std::vector<cv::Rect> foundLocations;


  int minNeighbours = 1;
  int flags = 0;

  _hogCPU->detectMultiScale(Frame, foundLocations);

  //cv::Rect target_rectangle = rectangleCheck(Frame, foundLocations);
  for (size_t i = 0; i < foundLocations.size(); i++)
  {
    cv::Rect r = foundLocations[i];
    rectangle(Frame, foundLocations[i], cv::Scalar(0, 0, 255), 3);
  }

  // std::vector<cv::Rect> detections;

  cv::Mat target_center = shirtColour(Frame);


  //cv::circle(Frame, cv::Point(target_center), 10, CV_RGB(255,255,255), 5);


  return target_center;
}

//checks if person detected is majority red
cv::Rect person_detector::rectangleCheck(cv::Mat Frame, std::vector<cv::Rect> foundLocations)
{
  cv::Vec3b colourCheck;
  for (size_t i = 0; i < foundLocations.size(); i++)
  {
    cv::Rect r = foundLocations[i];
    for (int x = 0; x < Frame.cols; x++)
    {
      for (int y = 0; y < Frame.rows; y++)
      {
        cv::Vec3b pixelVal = Frame.at<cv::Vec3b>(y, x);
        colourCheck =colourCheck + pixelVal;
      }
    }
  }
}

cv::Mat person_detector::shirtColour(cv::Mat Frame)
{
  cv::Mat HSVFrame;
  cv::Mat FilteredFrame;
  cv::cvtColor(Frame, HSVFrame, cv::COLOR_BGR2HSV);
  //isolate red colours in Frame to find targets T-shirt
  // defined Hue, Saturation, Value
  cv::inRange(HSVFrame, (120, 60, 0), (170, 100, 0), FilteredFrame);
  //use to find center of red mass
  //cv::Moments m = cv::moments(FilteredFrame, true);
  //cv::Point target_center(m.m10/m.m00, m.m01/m.m00);
  return FilteredFrame;
}
