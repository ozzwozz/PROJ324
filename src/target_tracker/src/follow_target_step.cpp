#include "follow_target_step.hpp"

geometry_msgs::Twist LinefollowerPID::PID(cv::Point msg)
{
  speedChange();
  geometry_msgs::Twist twist_to_publish = assignTwist(msg.x);
  return twist_to_publish;
}

geometry_msgs::Twist LinefollowerPID::assignTwist(int cx)
{
  static geometry_msgs::Twist twist_object;

  int error_x = cx - x_centre;
  //twist_object = Twist();
  twist_object.linear.x = 0.5;
  twist_object.angular.z = -error_x / 100;
  return twist_object;
}

int LinefollowerPID::speedChange()
{
  static int speedModifier;



  return speedModifier;
}
