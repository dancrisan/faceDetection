# faceDetection
Fun with OpenCV and C++ : an algo that detects where are the faces on a picture

Open cmd line where your faceDetection.cpp folder is and write:

1) g++ -ggdb `pkg-config --cflags opencv` -o `basename faceDetection.cpp .cpp` faceDetection.cpp `pkg-config --libs opencv`

2) ./faceDetection
