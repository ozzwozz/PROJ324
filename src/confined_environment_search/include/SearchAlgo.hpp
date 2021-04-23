#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

class SearchingMappedArea
{
	ros::NodeHandle nh_;

	ros ::Subscriber PoseSub_;

	ros::Publisher SearchGoal;
	ros::Publisher cameraPoint_pub_;

    
    typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
    
    move_base_msgs::MoveBaseGoal SearchGoal;
    
	private:
		void SearchCallback();
    void CollateTargetPose(int target_x_position, int target_w_orientation);

	protected:
		void ConvertMapToGraph();

	public:
		SearchingMappedArea()
		{
			PoseSub_ = nh_.subscribe("/odom", 1, &SearchingMappedArea::SearchCallback, this);

			SearchGoal = nh_.advertise("/move_base_simple/goal", 1);
            
            //tell the action client that we want to spin a thread by default
            MoveBaseClient ac("move_base", true);
            
            //wait for the action server to come up
            while(!ac.waitForServer(ros::Duration(5.0))){
              ROS_INFO("Waiting for the move_base action server to come up");
            }
		}
		~SearchingMappedArea()
		{

		}


};
