#include "camera.hpp"

Camera::Camera(int cameraIndex)
    : cameraIndex(cameraIndex) {
}

Camera::~Camera() {
    release();
}

bool Camera::open() {
    return camera.open(cameraIndex);
}

bool Camera::getFrame(cv::Mat& frame) {
    return camera.read(frame);
}

void Camera::release() {
    camera.release();
}