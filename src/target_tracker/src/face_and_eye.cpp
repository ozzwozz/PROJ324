#include <face_and_eye.hpp>

cv::Mat face_and_eye::face_and_eye_rectangles(cv::Mat Frame)
{
  //cv::Mat Frame = frame->image;
  cv::Mat greyFrame;
  cv::cvtColor(Frame, greyFrame, cv::COLOR_RGB2GRAY);
  cv::equalizeHist(greyFrame, greyFrame);

  hog.detectMultiScale(Frame, foundLocations, 1.1, 3, 0, cv::Size (30,30), cv::Size(60,60));



  /// draw detections and store location
  for( size_t i = 0; i < foundLocations.size(); i++ )
  {
    Rect r = foundLocations[i];
    cv::rectangle(Frame, foundLocations[i], cv::Scalar(0,0,255), 3);
    stringstream temp;
    temp << foundWeights[i];
    //putText(Frame, temp.str(),Point(foundLocations[i].x,foundLocations[i].y+50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255));
    //track.push_back(Point(foundLocations[i].x+foundLocations[i].width/2,foundLocations[i].y+foundLocations[i].height/2));
  }

  /// plot the track so far
  //for(size_t i = 1; i < track.size(); i++)
  //{
  //  line(frame, track[i-1], track[i], Scalar(255,255,0), 2);
  //}
  return Frame;
}
//winStride= (8,8)
