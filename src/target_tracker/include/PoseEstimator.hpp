#ifndef POSEESTIMATOR_HPP
#define POSEESTIMATOR_HPP

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <image_geometry/pinhole_camera_model.h>
#include <visualization_msgs/Marker.h>

class PoseEstimator
{
  ros::NodeHandle pose_nh_;
  // image_transport::ImageTransport pose_it_;
  // image_transport::Subscriber image_sub_;
  // image_transport::Publisher image_pub_;
  ros::Publisher marker_pub_;

  private:
    void get_markerMsgs(cv::Point3d point_msg);
    // void DepthCallback(const sensor_msgs::ImageConstPtr& msg);
    visualization_msgs::Marker target_marker;

    int depth;
    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    image_geometry::PinholeCameraModel PinholeCamera;

  protected:

  public:
    PoseEstimator()//: pose_it_(pose_nh_)
  {
    // Subscrive to input video feed and publish output video feed
    // Depth_sub_ = pose_it_.subscribe("/image/compressedDepth", 1, &PoseEstimator::DepthCallback, this);


    // image_sub_ = it_.subscribe("/image_converter/output_video", 1, &ImageConverter::imageCb, this);

    marker_pub_ = pose_nh_.advertise<visualization_msgs::Marker>("visualization_msgs", 1);
    //cv::namedWindow(OPENCV_WINDOW);

  }
  cv::Point3d convert2Dto3D(cv::Point point_msg, cv::Mat frame);
};
#endif
