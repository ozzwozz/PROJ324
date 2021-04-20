#include <PoseEstimator.hpp>

// void PoseEstimator::DepthCallback(const sensor_msgs::ImageConstPtr& msg)
// {
//   depth = cv::Point(msg.x, msg.y);
// }

void PoseEstimator::get_markerMsgs(cv::Point3d point_msg)
{
  target_marker.header.frame_id = "camera_sensor";
  //target_marker.header.stamp = ros::Time();
  target_marker.type = shape;
  target_marker.action = visualization_msgs::Marker::ADD;
  target_marker.pose.position.x = point_msg.x;//*0.01);//(point_msg.x/250);
  target_marker.pose.position.y = point_msg.y;//*0.01);//(point_msg.y/250);
  target_marker.pose.position.z = point_msg.z;

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
  marker_pub_.publish(target_marker);
}

cv::Point3d PoseEstimator::convert2Dto3D(cv::Point point_msg, cv::Mat frame)
{
  //point_msg = PinholeCamera.rectifyPoint(point_msg);
  cv::Point3d Point3d = PinholeCamera.projectPixelTo3dRay(point_msg);
  get_markerMsgs(Point3d);

  return Point3d;
}
