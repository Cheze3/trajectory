#include "camera.hpp"
#include <iostream>

int main() {
    Camera camera(0);

    if (!camera.open()) {
        std::cerr << "Could not open camera\n";
        return 1;
    }

    cv::Mat frame;

    while (true) {
        if (!camera.getFrame(frame)) {
            std::cerr << "Could not read frame\n";
            break;
        }

        cv::imshow("Camera", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}