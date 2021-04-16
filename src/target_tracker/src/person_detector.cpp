#include "person_detector.hpp"



//cv::Mat person_detector::person_tracker(cv::Mat OriginalFrame)
cv::Point person_detector::person_tracker(cv::Mat OriginalFrame)
{
  static std::vector<cv::Point> target_center;

  boost::scoped_ptr<cv::HOGDescriptor> _hogCPU;
  cv::HOGDescriptor hog;

  //re-trains the network every frame , this is an issue , this should only be done on initialisation
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

    _hogCPU->detectMultiScale(OriginalFrame, foundLocations);
    //cv::Rect target_rectangle = rectangleCheck(Frame, foundLocations);
    for (size_t i = 0; i < foundLocations.size(); i++)
    {
      cv::Rect r = foundLocations[i];
      rectangle(Frame, foundLocations[i], cv::Scalar(0, 0, 255), 3);
    }

    cv::Mat targets_filtered = shirtColour(Frame);

    cv::Rect Target_Box = pixelcount(targets_filtered, foundLocations);

    if (Target_Box.area() > 0)
    {
      rectangle(Frame, Target_Box, cv::Scalar(255, 0, 0), 3);//BGR
    }

    static std::vector<cv::Point> predictive_points;
    static int predictionTracker;
    cv::Point target_follow_point;

    //get centre of target person
    cv::Point temp = GetTargetCenter(Target_Box);
    if (temp.x != 0 && temp.y != 0)
    {
      target_center.push_back(temp);
      Frame = MovementLine(target_center, Frame, cv::Scalar(255, 0, 0));

      std::vector<cv::Point> RateofMovement = CalculateRateOfMovement(target_center);
      predictive_points.clear();
      predictive_points = MakeEstimation(RateofMovement, temp);
      predictionTracker = 0;

      target_follow_point = temp;

    }
    else
    {
      if (predictionTracker >= 0 && predictionTracker <= 5)
      {
        if(predictive_points.size() > predictionTracker )
        {
          //cv::rectangle(Frame, predictive_points[predictionTracker], cv::Scalar(0, 255, 0), 3);//BGR
          circle(Frame, cv::Point(predictive_points[predictionTracker]), 5, cv::Scalar(255, 0, 0), 3);//BGR
          predictionTracker++;
        }
      }
      target_follow_point = predictive_points[predictionTracker];
    }

    Frame = MovementLine(target_center, Frame, cv::Scalar(255, 0, 0));
    Frame = MovementLine(predictive_points, Frame, cv::Scalar(0, 255, 0));

  return target_follow_point;
}

std::vector<cv::Point> person_detector::CalculateRateOfMovement(std::vector<cv::Point> KnownPoints /*Timestamp for points*/)
{
  std::vector<cv::Point> RateofMovement;
  int KnownPoints_size = KnownPoints.size();

  if(KnownPoints_size>=2)
  {
    for (int x = 0; x < std::min(5, KnownPoints_size); x++)
    {
      //this line is to the effect of change in position / change in time = relative speed
      RateofMovement.push_back(KnownPoints[KnownPoints_size-(x+1)] - KnownPoints[KnownPoints_size-(x+2)])/*/(timestamp[x] - timestamp[x-1])*/;
    }
  }
  return RateofMovement;
}

std::vector<cv::Point> person_detector::MakeEstimation(std::vector<cv::Point> relative_movement, cv::Point LastPrecise)
{
  std::vector<cv::Point> Predictive_Points;
  int rel_movement_size = relative_movement.size();
  Predictive_Points.push_back(LastPrecise);

  cv::Point temp;

  if (rel_movement_size > 0)
  {
    for(int x = 0; x < rel_movement_size; x++)
    {
      temp += relative_movement[x];
    }
    temp = temp/rel_movement_size;

    for(int x = 0; x < std::min(5, rel_movement_size); x++)
    {
      //Predictive_Points.push_back(Predictive_Points[x] + relative_movement[rel_movement_size-(x+1)]);
      Predictive_Points.push_back(Predictive_Points[x] + temp);
    }
  }
  return Predictive_Points;
}

cv::Point person_detector::GetTargetCenter(cv::Rect Target_Box)
{
  int TBwidth = Target_Box.x + (Target_Box.width / 2);
  int TBheight = Target_Box.y + (Target_Box.height / 2);

  cv::Point target_point(TBwidth, TBheight);

  return target_point;
}

cv::Mat person_detector::MovementLine(std::vector<cv::Point> target_center, cv::Mat CurrentFrame, cv::Scalar LineColour)
{
  if (target_center.size() >= 2)
  {
    for(size_t x = 1; x < target_center.size(); x++)
    {
      cv::line(CurrentFrame, target_center[x], target_center[x-1], LineColour, 2);
    }
  }
  return CurrentFrame;
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
  return FilteredFrame;
}
