#include <target_marker_node.hpp>


void target_marker_node::target_marker_callback(cv::Point point_msg)//const visualisation_msgs::Marker& msg)
{
  //int data = getLaserDataAtAngle();


  get_markerMsgs(point_msg);
  marker_pub_.publish(target_marker);
}

void target_marker_node::get_markerMsgs(cv::Point point_msg)
{
  target_marker.header.frame_id = "/map";
  //target_marker.header.stamp = ros::Time();
  target_marker.type = shape;
  target_marker.action = 0;//visualization_msgs::Marker::ADD;
  target_marker.pose.position.x = -point_msg.x;//*0.01);//(point_msg.x/250);
  target_marker.pose.position.y = -point_msg.y;//*0.01);//(point_msg.y/250);
  // target_marker.pose.position.z = 1;

  target_marker.pose.orientation.x = 0.0;
  target_marker.pose.orientation.y = 0.0;
  target_marker.pose.orientation.z = 0.0;
  target_marker.pose.orientation.w = 1.0;

  target_marker.scale.x = 0.5;
  target_marker.scale.y = 0.5;
  target_marker.scale.z = 1.5;

  target_marker.color.a = 1.0;
  target_marker.color.r = 1.0;
  //target_marker.lifetime = 1;
}

void target_marker_node::update_position(int target_object_position)
{
  // target_marker.pose.position.x = -point_msg.x;//*0.01);//(point_msg.x/250);
  // target_marker.pose.position.y = -point_msg.y;//*0.01);//(point_msg.y/250);
  //target_marker.pose.position.z = 1;
}

void target_marker_node::getLaserDataAtAngle(const sensor_msgs::LaserScan& msg, unsigned int AngleFromCentre)
{
  //sensor_msgs::LaserScan& msgPtr = msg;
  LaserData[0] = msg.ranges[(LaserRays / 2) - ((AngleFromCentre*LasersPerDegree)-2)];
  LaserData[1] = msg.ranges[(LaserRays / 2) - ((AngleFromCentre*LasersPerDegree)-1)];
  LaserData[2] = msg.ranges[(LaserRays / 2) - ((AngleFromCentre*LasersPerDegree)+0)];
  LaserData[3] = msg.ranges[(LaserRays / 2) - ((AngleFromCentre*LasersPerDegree)+1)];
  LaserData[4] = msg.ranges[(LaserRays / 2) - ((AngleFromCentre*LasersPerDegree)+2)];

}
