#ifndef FOLLOW_TARGET_STEP_HPP
#define FOLLOW_TARGET_STEP_HPP

#include <ros/ros.h>

#include <geometry_msgs/Twist.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class LinefollowerPID
{
  private:
    geometry_msgs::Twist assignTwist(int cx);
    int x_centre;
    int y_centre;
  protected:


  public:
    LinefollowerPID(int xSize, int ySize)
    {
      x_centre = xSize / 2;
      y_centre = ySize / 2;

    }
    ~LinefollowerPID()
    {

    }
    geometry_msgs::Twist PID(cv::Point msg);
    int speedChange();

};

#endif
