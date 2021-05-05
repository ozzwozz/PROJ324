#ifndef FOLLOW_TARGET_STEP_HPP
#define FOLLOW_TARGET_STEP_HPP

#include <ros/ros.h>

#include <geometry_msgs/Twist.h>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <actionlib_msgs/GoalID.h>

class LinefollowerPID
{
  private:
    geometry_msgs::Twist assignTwist(int cx);
    int x_centre;
    int y_centre;

    ros::NodeHandle goal_nh_;
    ros::Publisher goalCancel_Pub_;
    ros::Subscriber clock_Sub_;
    actionlib_msgs::GoalID GoalCancel;
    protected:
    void ClassClean();
    void updateTime();

    ros::Time TimeSinceStart;
  public:
    LinefollowerPID(int xSize, int ySize)
    {
      x_centre = xSize / 2;
      y_centre = ySize / 2;

      //clock_Sub_ = goal_nh_.subscribe("Time", 1000, updateTime);
      goalCancel_Pub_ = goal_nh_.advertise<actionlib_msgs::GoalID>("GoalID",1000);
    }
    ~LinefollowerPID()
    {

    }
    geometry_msgs::Twist PID(cv::Point msg);
    int speedChange();
    actionlib_msgs::GoalID GetCancelMsg();
};

#endif
