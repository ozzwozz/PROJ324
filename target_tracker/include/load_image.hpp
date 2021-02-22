#ifndef LOAD_IMAGE_H
#define LOAD_IMAGE_H

#include <ros/ros.h>
#include <std_msgs/String.h>
// include opencv2
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

// include CVBridge, ImageTransport, Image msg
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

class loadImage
{
	private:
		std::string OPENCV_WINDOW = "image window";
		
		// Topic Declarations
		std::string ImageTopic = "/camera/rgb/image_raw";
		std::string PublishTopic = "/image_converter/output_video";

		// Publisher & subscriber
		ros::Publisher ImagePublisher;
		ros::Subscriber ImageSubscriber;
		// filepath to images
		std::string imagePath = "/home/user/Documents/catkin_ws";
		
		// instantiate the ROS node handler
		ros::NodeHandle ImageNode;
		//instantiate the Image Transporter
		image_transport::ImageTransport ImageTransporter(const ros::NodeHandle& ImageNode);
		// methods
		void imgmsg_ConvertTo_cv2();
	protected:

	public:
		loadImage()
		{

			// subscribe to the image topic
			image_transport::Subscriber ImageSubscriber = ImageTransporter.subscribe(ImageTopic, 1, imgmsg_ConvertTo_cv2);
			// advertise the analysed video stream
			image_transport::Publisher ImagePublisher = ImageTransporter.advertise(PublishTopic, 1);
			cv::namedWindow(OPENCV_WINDOW);
		}
		
		~loadImage()
		{
			cv::destroyWindow(OPENCV_WINDOW);
		}
};

#endif	// LOAD_IMAGE_H

