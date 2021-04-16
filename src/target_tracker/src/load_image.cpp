#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <face_and_eye.hpp>
#include <person_detector.hpp>
#include <follow_target_step.hpp>

static const std::string OPENCV_WINDOW = "Image window";


class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;
  ros::Publisher cmd_vel_pub_;
public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1, &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    //followpoint_pub = nh_.advertise<std_msgs::String>("/target_tracker/target_point", 1)
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
    //Frame = p_detector->person_tracker(Frame);

    cv::Point point_msg = p_detector->person_tracker(Frame);

    cv::Point point_msg;

    geometry_msgs::Twist twist_to_publish = followerPID_object.PID(point_msg);

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, Frame);
    waitKey(10);

    // Output modified video stream
    //image_pub_.publish(cv_ptr->toImageMsg());
    // publish target point
    cmd_vel_pub_.publish(twist_to_publish);
  }
};

int main(int argc, char** argv)
{
  //ros::Rate r(10);
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  while(ros::ok())
  {
    ros::spinOnce();
  //r.sleep();
  }
  return 0;
}
