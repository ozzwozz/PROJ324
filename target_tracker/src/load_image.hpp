#include <ros/ros.h>

//include opencv2
#include <opencv2/opencv.hpp>


//include CVBridge, ImageTransport, Image msg
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

class loadImage
{
	private:
		static const std::string OpenCVWindow = "image window";
		
		//Topic Declarations
		static const std::string ImageTopic = "/camera/rgb/image_raw";
		static const std::string PublishTopic = "/image_converter/output_video";

		//Publisher & subscriber
		ros::Publisher ImagePublisher;
		ros::Subscriber ImageSubscriber;
		//filepath to images
		static const std::string imagePath = "/home/user/Documents/catkin_ws"
		
		//instantiate the ROS node handler
		ros::Nodehandle ImageNode;

		//instantiate the Image Transporter
		image_transport::ImageTransport ImageTransporter;

		//methods
		void imgmsg_ConvertTo_cv2();
	protected:

	public:
		loadImage() : ImageT
		{
			//subscribe to the image topic
			ImageSubscriber = ImageTransporter.subscribe(ImageTopic, 1, imgmsg_ConvertTo_cv2, this);
			//advertise the analysed video stream
			ImagePublisher = ImageTransporter.advertise(PublishTopic, 1);

			cv::namedWindow(OPENCV_WINDOW);
		}
		
		~loadImage()
		{
			cv::destroyWindow(OPENCV_WINDOW);
		}

};
