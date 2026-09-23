#pragma once

#include <opencv2/opencv.hpp>

class Camera {
public:
    Camera(int cameraIndex);
    ~Camera();

    bool open();
    bool getFrame(cv::Mat& frame);
    void release();

private:
    int cameraIndex;
    cv::VideoCapture camera;
};