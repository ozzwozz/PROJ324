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
			GraphMatrix[x][y] = ;
		}
	}
}


void SearchingMappedArea::SearchCallback(const nav_msgs::Odometry& msg)
{



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
