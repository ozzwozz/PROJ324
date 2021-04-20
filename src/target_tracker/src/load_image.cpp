#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <face_and_eye.hpp>
#include <person_detector.hpp>
#include <follow_target_step.hpp>
#include <target_marker_node.hpp>
#include "PoseEstimator.hpp"

static const std::string OPENCV_WINDOW = "Image window";


class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  ros::Publisher cmd_vel_pub_;
  ros::Publisher cameraPoint_pub_;
  private:
    geometry_msgs::Twist twist_to_publish;

public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/summit_xl_control/cmd_vel", 1);
    cv::namedWindow(OPENCV_WINDOW);

  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {

    person_detector *p_detector;
    cv_bridge::CvImagePtr cv_ptr;

    LinefollowerPID followerPID_object(1080,720);
    target_marker_node target_marker_node;
    PoseEstimator PoseEstimator;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      cv::resize(cv_ptr->image, cv_ptr->image, Size(1080,720));
      cv::flip(cv_ptr->image, cv_ptr->image, 0);
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    cv::Mat Frame = cv_ptr->image;

    cv::Point point_msg = p_detector->person_tracker(Frame);

    unsigned int target_angle = p_detector->angleFromCentre(point_msg);
    // //cv::Point point_msg;
    if (point_msg.x > 0 && point_msg.y > 0)
    {
       twist_to_publish = followerPID_object.PID(point_msg);
       //target_marker_node.target_marker_callback(point_msg);

       PoseEstimator.convert2Dto3D(point_msg, cv_ptr->image);
    }

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, Frame);
    waitKey(10);

    //image_pub_.publish(msg);
    // publish target point
    cmd_vel_pub_.publish(twist_to_publish);
  }
};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  while(ros::ok())
  {
    ros::spinOnce();
  }
  return 0;
}
