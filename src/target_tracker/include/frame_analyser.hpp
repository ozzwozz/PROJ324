#ifndef FRAME_ANALYSER_HPP
#define FRAME_ANALYSER_HPP

// include opencv2
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class frame_analyser
{
	public:	
	//class constructor
	frame_analyser()
	{
		
	}
	~frame_analyser()
	{

	}
	Mat GetProcessedImage();

	protected:

	private:
	void HogDetect();
	void PeopleDetect();
};

#endif
