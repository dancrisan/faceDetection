#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

vector < vector<Point> > detectAndDisplay(Mat frame);

// to find where your module is, type "locate haarcascade_frontalface_alt.xml" in your cmd line
string face_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;

int main(void)
{
  vector < vector<Point> > faceDetectionVector;

  // Load the cascade
  if (!face_cascade.load(face_cascade_name))
  {
      printf("Couldn't load face cascade module\n");
      return (-1);
  };

  // Read the image file
  Mat frame = imread("lenna.png");

  if (!frame.empty())
  {
      faceDetectionVector = detectAndDisplay(frame); //the magic happens here : detects faces from a pic
      waitKey(0);
  }
  else
      printf("Are you sure you have the correct filename?\n");

  return 0;
}

// detecs faces and displays them in the picture
vector < vector<Point> > detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    vector<Point> faceCoords;
    vector < vector<Point> > faceVector;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    int i;

    for (i = 0; i < faces.size(); i++) // Iterate through all detected faces
    {
        Point pt1(faces[i].x, faces[i].y); // Display detected faces on main window
        faceCoords.push_back(pt1);
        Point pt2((faces[i].x + faces[i].height), (faces[i].y + faces[i].width));
        faceCoords.push_back(pt2);
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);

        faceVector.push_back(faceCoords);
        faceCoords.clear();
    }

    imshow("original", frame);

    return faceVector;
}
