#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

// Function Headers
vector < vector<Point> > detectAndDisplay(Mat frame);

// Global variables
// Copy this file from opencv/data/haarscascades to target folder
string face_cascade_name = "/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
string window_name = "Capture - Face detection";
string filename;

// Function main
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
    Mat frame = imread("group.JPG");
    //Mat frame = imread("lenna.png");


    //for (;;)
    //{
        // Apply the classifier to the frame
        if (!frame.empty())
        {
            faceDetectionVector = detectAndDisplay(frame);
            waitKey(0);
            //break;
        }
        else
        {
            printf("Are you sure you have the correct filename?\n");
            //break;
        }

        // int c = waitKey(10);
        //
        // if (27 == char(c))
        // {
        //     break;
        // }
    //}
    cout << faceDetectionVector.size() << endl;
    return 0;
}

// //face detector
// int faceDetector()
// {
//     // Load the cascade
//     if (!face_cascade.load(face_cascade_name))
//     {
//         printf("Couldn't load face cascade module\n");
//         return (-1);
//     };
//
//     // Read the image file
//     Mat frame = imread(filename);
//
//     for (;;)
//     {
//         // Apply the classifier to the frame
//         if (!frame.empty())
//         {
//             detectAndDisplay(frame);
//         }
//         else
//         {
//             printf("Did you mispelled your filename?");
//             break;
//         }
//
//         int c = waitKey(10);
//
//         if (27 == char(c))
//         {
//             break;
//         }
//     }
//
//     return 0;
// }



// Function detectAndDisplay
vector < vector<Point> > detectAndDisplay(Mat frame)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    Mat crop;
    Mat res;
    Mat gray;
    string text;
    stringstream sstm;
    vector<Point> faceCoords;
    vector < vector<Point> > faceVector;

    //vector <vector <int x, int y> > coords;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    // Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

    // Set Region of Interest
    cv::Rect roi_b;
    cv::Rect roi_c;

    size_t ic = 0; // ic is index of current element
    int ac = 0; // ac is area of current element

    size_t ib = 0; // ib is index of biggest element
    int ab = 0; // ab is area of biggest element

    for (ic = 0; ic < faces.size(); ic++) // Iterate through all current elements (detected faces)

    {
        roi_c.x = faces[ic].x;
        roi_c.y = faces[ic].y;
        roi_c.width = (faces[ic].width);
        roi_c.height = (faces[ic].height);

        ac = roi_c.width * roi_c.height; // Get the area of current element (detected face)

        roi_b.x = faces[ib].x;
        roi_b.y = faces[ib].y;
        roi_b.width = (faces[ib].width);
        roi_b.height = (faces[ib].height);

        ab = roi_b.width * roi_b.height; // Get the area of biggest element, at beginning it is same as "current" element

        if (ac > ab)
        {
            ib = ic;
            roi_b.x = faces[ib].x;
            roi_b.y = faces[ib].y;
            roi_b.width = (faces[ib].width);
            roi_b.height = (faces[ib].height);
        }

        crop = frame(roi_b);
        resize(crop, res, Size(128, 128), 0, 0, INTER_LINEAR); // This will be needed later while saving images
        cvtColor(crop, gray, CV_BGR2GRAY); // Convert cropped image to Grayscale

        Point pt1(faces[ic].x, faces[ic].y); // Display detected faces on main window - live stream from camera
        faceCoords.push_back(pt1);
        Point pt2((faces[ic].x + faces[ic].height), (faces[ic].y + faces[ic].width));
        faceCoords.push_back(pt2);
        rectangle(frame, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
        //cout << faceCoords.size() << endl;
        //cout << faceCoords[0] << endl;
        //cout << faceCoords[1] << endl;
        faceVector.push_back(faceCoords);
        faceCoords.clear();
        //cout << faceCoords.size() << endl;
        //cout << faceVector.size() << endl;
        //cout << faceVector[0] << endl;
        //cout << faceVector[1] << endl;
        //cout << faces[ic].x << endl;
        //printf("Coord 2 is " + faces[ic].y);
        //coords.push(vector <pt1, pt2>);
        //coords.size();
    }

    // Show image
    //sstm << "Crop area size: " << roi_b.width << "x" << roi_b.height << " Filename: " << filename;
    //text = sstm.str();

    //putText(frame, text, cvPoint(30, 30), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 255), 1, CV_AA);
    imshow("original", frame);

    return faceVector;
    //return coords;

}
