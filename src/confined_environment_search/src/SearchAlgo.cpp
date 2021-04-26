#include <SearchAlgo.hpp>

void SearchingMappedArea::ConvertMapToGraph()
{
	int mapwidth;
	int mapheight;
	int GraphMatrix[mapwidth][mapheight];
	for (int x = 0; x < mapwidth; x++)
	{
		for (int y =0; y < mapheight; y++)
		{
			if (GraphMatrix[x][y] == '0')
			GraphMatrix[x][y] = 0;
		}
	}
}


void SearchingMappedArea::SearchCallback(const nav_msgs::Odometry& msg)
{
    CalculateNextPose();
    CollateTargetPose(target_x_position, target_w_orientation);
    GoalStateCheck();

}

void SearchingMappedArea::CalculateNextPose()
{

}

void SearchingMappedArea::GoalStateCheck()
{
    ROS_INFO("Sending goal");
    ac.sendGoal(SearchGoal);

    ac.waitForResult();

    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    {
      ROS_INFO("Hooray, the base moved 1 meter forward");
    }
    else if(ac.getState() == actionlib::SimpleClientGoalState::ABORTED)
    {
        ROS_INFO("Move has been aborted due to target aquisition");
    }
    else
    {
        ROS_INFO("The base failed to move forward 1 meter for some reason");
    }
}

void SearchingMappedArea::CollateTargetPose(int target_x_position, int target_w_orientation)
{
    //we'll send a goal to the robot to move 1 meter forward
    SearchGoal.target_pose.header.frame_id = "summit_xl_a_base_footprint";
    SearchGoal.target_pose.header.stamp = ros::Time::now();

    SearchGoal.target_pose.pose.position.x = target_x_position;
    SearchGoal.target_pose.pose.orientation.w = target_w_orientation;
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "area_search");
    SearchingMappedArea SearchMappedArea;

    while(ros::ok())
    {
        ros::spinOnce();
    }
    return 0;
}
