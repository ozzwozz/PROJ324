#include "load_image.hpp"


//convert camera data from img_msg to cv2 format for manipulation
void imgmsg_ConvertTo_cv2()
{
	ROS_INFO("image topic notified");
	cv_bridge::cvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	if(cv_ptr->image.rows > 60 && cv_ptr->image.cols > 60)
	{
		cv::circle(cv_ptr->image, cv::Point(50,50), 10, CV_RGB(255,0,0));
	}
	cv::imshow(OPENCV_WINDOW, cv_ptr->image);
	cv::waitKey(3);
	
	//output modified stream
	ImagePublisher.publish(cv_ptr->toImageMsg);
}

int main(int argc, char** argv)
{
	//initialise the ROS listener node
	ros::init(argc, argv, "listener");
	ImageConverter ic;	
	ros::spin;
	return 0;
}
