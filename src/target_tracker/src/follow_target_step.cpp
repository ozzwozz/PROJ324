#include "follow_target_step.hpp"

geometry_msgs::Twist LinefollowerPID::PID(cv::Point msg)
{
  speedChange();
  geometry_msgs::Twist twist_to_publish = assignTwist(msg.x);
  actionlib_msgs::GoalID GoalCancel = GetCancelMsg();
  goalCancel_Pub_.publish(GoalCancel);
  return twist_to_publish;
}

geometry_msgs::Twist LinefollowerPID::assignTwist(int cx)
{
  static geometry_msgs::Twist twist_object;

  int error_x = x_centre - cx;
  //twist_object = Twist();
  twist_object.linear.x = -error_x / 100;
  twist_object.angular.z = 0.5;
  return twist_object;
}

actionlib_msgs::GoalID LinefollowerPID::GetCancelMsg()
{
  GoalCancel.stamp = ros::Time::now();
  GoalCancel.id = "";
  return GoalCancel;
}

int LinefollowerPID::speedChange()
{
  static int speedModifier;



  return speedModifier;
}

void LinefollowerPID::ClassClean()
{

}
