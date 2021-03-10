#include <face_and_eye.hpp>

cv::Mat face_and_eye::face_and_eye_rectangles(cv::Mat Frame)
{
  cv::CascadeClassifier cascade; // creates the hog descriptor and detector
  cascade.load("/home/oscar/Documents/catkin_ws/src/target_tracker/cascades_training/frontal_face.xml");

  //cv::Mat Frame = frame->image;
  cv::Mat greyFrame;
  cv::cvtColor(Frame, greyFrame, cv::COLOR_BGR2GRAY);
  cv::equalizeHist(greyFrame, greyFrame);
  std::vector<cv::Rect> foundLocations;

  cascade.detectMultiScale(greyFrame, foundLocations, 1.01);

  //draw detections and store location
  //for( size_t i = 0; i < foundLocations.size(); i++ )
  //{
  //Rect r = foundLocations[i];
  for(int i = 0; i < foundLocations.size(); i++)
  {
  cv::Rect r = foundLocations[i];
  int x = r.x;
  int y = r.y;
  int w = r.width;
  int h = r.height;
  cv::rectangle(Frame, Point(x,y), Point(x+w,y+h), cv::Scalar(0,255,0), 3);
  }
  //   stringstream temp;
  //   temp << foundWeights[i];
  //   //putText(Frame, temp.str(),Point(foundLocations[i].x,foundLocations[i].y+50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,255));
  //   //track.push_back(Point(foundLocations[i].x+foundLocations[i].width/2,foundLocations[i].y+foundLocations[i].height/2));
  //}

  /// plot the track so far
  //for(size_t i = 1; i < track.size(); i++)
  //{
  //  line(frame, track[i-1], track[i], Scalar(255,255,0), 2);
  //}
  return greyFrame;
}
//winStride= (8,8)
