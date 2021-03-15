#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <face_and_eye.hpp>
#include <person_detector.hpp>

static const std::string OPENCV_WINDOW = "Image window";

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_;
  image_transport::Publisher image_pub_;

public:
  ImageConverter()
    : it_(nh_)
  {
    // Subscrive to input video feed and publish output video feed
    image_sub_ = it_.subscribe("/camera/rgb/image_raw", 1,
      &ImageConverter::imageCb, this);
    image_pub_ = it_.advertise("/image_converter/output_video", 1);

    cv::namedWindow(OPENCV_WINDOW);
  }

  ~ImageConverter()
  {
    cv::destroyWindow(OPENCV_WINDOW);
  }

  void imageCb(const sensor_msgs::ImageConstPtr& msg)
  {

    face_and_eye *thing;
    person_detector *p_detector;
    cv_bridge::CvImagePtr cv_ptr;
    try
    {
      cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      cv::resize(cv_ptr->image, cv_ptr->image, Size(1080,720));
    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    cv::Mat Frame = cv_ptr->image;
    //Frame = thing->face_and_eye_rectangles(Frame);
    Frame = p_detector->person_tracker(Frame);

    // Update GUI Window
    cv::imshow(OPENCV_WINDOW, Frame);
    waitKey(10);
    //while(cv::waitKey(30)!='x'){cv::imshow(OPENCV_WINDOW, Frame);};

    // Output modified video stream
    //image_pub_.publish(cv_ptr->toImageMsg());
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
