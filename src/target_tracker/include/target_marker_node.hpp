#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>
#include <visualization_msgs/Marker.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <sensor_msgs/LaserScan.h>

class target_marker_node
{
  ros::NodeHandle nh_;

  ros::Publisher marker_pub_;

  private:
    //geometry_msgs::Twist twist_to_publish;
    visualization_msgs::Marker target_marker;

    int cameraFOV = 60;
    int LaserScanFOV = 240;
    int ignoredLaser = (LaserScanFOV / 2) - (cameraFOV / 2); // the angle of laser data not in the visible range of the camera
    // number of rays from the laser
    int LaserRays = 684;
    int LasersPerDegree = LaserRays / LaserScanFOV;
    int LaserData[5];


    uint32_t shape = visualization_msgs::Marker::CYLINDER;
    void update_position(int people_object_position);
public:
  target_marker_node()
  {
    marker_pub_ = nh_.advertise<visualization_msgs::Marker>("visualization_msgs", 1);

  }

  ~target_marker_node()
  {

  }

  void target_marker_callback(cv::Point point_msg);//const visualisation_msgs::Marker& msg)


  void get_markerMsgs(cv::Point point_msg);
  void getLaserDataAtAngle(const sensor_msgs::LaserScan& msg, unsigned int AngleFromCentre);

};
