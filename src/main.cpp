#include "camera.hpp"
#include "detector.hpp"
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

        cv::Point ballPosition;

        if (detectBall(frame, ballPosition)) {

            cv::circle(
                frame,
                ballPosition,
                20,
                cv::Scalar(0, 0, 255),
                2
            );

            std::cout
                << "Ball: ("
                << ballPosition.x
                << ", "
                << ballPosition.y
                << ")\n";
        }

        cv::imshow("Camera", frame);

        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    return 0;
}