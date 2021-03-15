#include "person_detector.hpp"

cv::Mat person_detector::person_tracker(cv::Mat OriginalFrame)
{
  boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
  cv::HOGDescriptor hog;

  //re-trains the network every frame , this is an issue , this should only be done on initialisation
  //hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
  //hog.load("/home/oscar/Documents/test_ws/src/target_tracker/cascades_training/hogcascase_pedestrian.xml");
  _hogCPU.reset( new cv::HOGDescriptor );
  _hogCPU->setSVMDetector( cv::HOGDescriptor::getDefaultPeopleDetector() );

  cv::Mat greyFrame;
  cv::Mat greyEqFrame;

  //cv::cvtColor(OriginalFrame, greyFrame, cv::COLOR_BGR2GRAY);
  //cv::equalizeHist(greyFrame, greyEqFrame);

  cv::Mat Frame = OriginalFrame;
  std::vector<cv::Rect> foundLocations;


  int minNeighbours = 1;
  int flags = 0;

  //hog.detectMultiScale(Frame, foundLocations);
  //if (!Frame.empty())
  //{
    _hogCPU->detectMultiScale(OriginalFrame, foundLocations);
    //cv::Rect target_rectangle = rectangleCheck(Frame, foundLocations);
    for (size_t i = 0; i < foundLocations.size(); i++)
    {
      cv::Rect r = foundLocations[i];
      rectangle(Frame, foundLocations[i], cv::Scalar(0, 0, 255), 3);
    }

    // std::vector<cv::Rect> detections;

    cv::Mat target_center = shirtColour(Frame);

    //cv::Mat OverlayedImage = imageOverlay(Frame, target_center, OriginalFrame);
    cv::Rect Target_Box = pixelcount(target_center, foundLocations);


    //cv::Rect Target_Box = rectangleCheck(Frame, foundLocations);

    if (Target_Box.area() > 0)
    {
      rectangle(Frame, Target_Box, cv::Scalar(255, 0, 0), 3);//BGR
    }
    //cv::circle(Frame, cv::Point(target_center), 10, CV_RGB(255,255,255), 5);
  //}

  return Frame;
}

cv::Rect person_detector::pixelcount(cv::Mat FilteredFrame, std::vector<cv::Rect> foundLocations)
{
  cv::Rect Target_Confirmed;
  int pixelCount;
  cv::Vec3b colourCheck;
  for (size_t i = 0; i < foundLocations.size(); i++)
  {
    cv::Rect r = foundLocations[i];
    for (int x = r.x; x < (r.x + r.width); x++)
    {
      for (int y = r.y; y < (r.y + r.height); y++)
      {
        cv::Vec3b pixelVal = FilteredFrame.at<cv::Vec3b>(y, x);
        if ((pixelVal[0]+pixelVal[1]+pixelVal[2]) == 255)
        {
          pixelCount+=1;
        }
      }
    }
    if (pixelCount > ((r.width*r.height)/3))
    {
      Target_Confirmed = foundLocations[i];
    }
  }
  return Target_Confirmed;
}

//checks if person detected is majority red
cv::Rect person_detector::rectangleCheck(cv::Mat Frame, std::vector<cv::Rect> foundLocations)
{
  cv::Rect Target_Confirmed;
  cv::Vec3b colourCheck;
  for (size_t i = 0; i < foundLocations.size(); i++)
  {
    cv::Rect r = foundLocations[i];
    for (int x = r.x; x < (r.x + r.width); x++)
    {
      for (int y = r.y; y < (r.y + r.height); y++)
      {
        cv::Vec3b pixelVal = Frame.at<cv::Vec3b>(y, x);
        colourCheck[0] =+ pixelVal[0];
        colourCheck[1] =+ pixelVal[1];
        colourCheck[2] =+ pixelVal[2];
      }
    }
    colourCheck[0] = colourCheck[0] / (r.width*r.height);
    colourCheck[1] = colourCheck[1] / (r.width*r.height);
    colourCheck[2] = colourCheck[2] / (r.width*r.height);
    if(colourCheck[0] > 120 && colourCheck[1] > 70 && colourCheck[2] > 70)
    {
      if(colourCheck[0] < 170 && colourCheck[1] < 130 && colourCheck[2] < 130)
      {
        // This is the person to track
        Target_Confirmed = foundLocations[i];
      }
    }
  }
  return Target_Confirmed;
}

cv::Mat person_detector::imageOverlay(cv::Mat WorkingFrame, cv::Mat FilteredFrame, cv::Mat OriginalFrame)
{
  cv::Mat OverlayedFrame;
  try
  {
    //bitwise_and(WorkingFrame, WorkingFrame, FilteredFrame);
    //cv::compare(WorkingFrame, FilteredFrame, OverlayedFrame);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
  }

  return OverlayedFrame;
}

cv::Mat person_detector::shirtColour(cv::Mat Frame)
{
  cv::Mat HSVFrame;
  cv::Mat FilteredFrame;
  cv::cvtColor(Frame, HSVFrame, cv::COLOR_BGR2HSV);
  //isolate red colours in Frame to find targets T-shirt
  // defined Hue, Saturation, Value
  cv::inRange(HSVFrame, cv::Scalar(0, 20, 75), cv::Scalar(40, 100, 150), FilteredFrame);
  //cv::inRange(Frame, cv::Scalar(10, 5, 5), cv::Scalar(190, 160, 160), FilteredFrame);
  //use to find center of red mass
  //cv::Moments m = cv::moments(FilteredFrame, true);
  //cv::Point target_center(m.m10/m.m00, m.m01/m.m00);
  return FilteredFrame;
}
