class SearchingMappedArea
{
	ros::NodeHandle nh_;

	ros ::Subscriber PoseSub_;

	ros::Publisher SearchGoal;
	ros::Publisher cameraPoint_pub_;

	SearchGoal;
	private:
		void SearchCallback();
	protected:
		void ConvertMapToGraph();

	public:
		SearchingMappedArea()
		{
			PoseSub_ = nh_.subscribe("/odom", 1, &SearchingMappedArea::SearchCallback, this);

			SearchGoal = nh_.advertise("/move_base_simple/goal", 1);
		}
		~SearchingMappedArea()
		{

		}


};
