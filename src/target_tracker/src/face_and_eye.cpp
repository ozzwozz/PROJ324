#include <face_and_eye.hpp>

cv_bridge::CvImagePtr face_and_eye::face_and_eye_rectangles(const cv_bridge::CvImagePtr frame)
{
  cv::Mat Frame = .toImageMsg();
  // convert to grey for faster processing
  //cv::Mat greyFrame = cv::cvtColor(frame, cv::COLOR_RGB2GRAY);
  // detect people in the current image
  cv::HOGDescriptor::detectMultiScale(Frame.toImageMsg, foundLocations, foundWeights);
  /// draw detections and store location
  for( size_t i = 0; i < foundLocations.size(); i++ )
  {
    Rect r = foundLocations[i];
    cv::rectangle(Frame, foundLocations[i], cv::Scalar(0,0,255), 3);
    stringstream temp;
    temp << foundWeights[i];
    //putText(frame, temp.str(),Point(foundLocations[i].x,foundLocations[i].y+50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255));
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
