#include "camera.hpp"
#include "detector.hpp"
#include "tracker.hpp"
#include "trajectory.hpp"
#include <iostream>
 
int main() {
    bool showMask = false;
    Camera camera(0);
 
    if (!camera.open()) {
        std::cerr << "Could not open camera\n";
        return 1;
    }
 
    cv::Mat frame;
 
    BallTracker tracker;
    std::vector<cv::Point> lastPrediction;
 
    while (true) {
        if (!camera.getFrame(frame)) {
            std::cerr << "Could not read frame\n";
            break;
        }
 
        cv::Point ballPosition;
        cv::Mat mask;
 
        if (detectBall(frame, ballPosition, mask)) {
 
            tracker.addPosition(ballPosition);
 
            if (tracker.hasEnoughHistory()) {
                lastPrediction = predictTrajectory(tracker.getHistory());
            }
 
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
        
 
        if (!lastPrediction.empty()) {
            cv::polylines(
                frame,
                lastPrediction,
                false,
                cv::Scalar(0, 255, 0),
                2
            );
        }
 
        cv::imshow("Camera", frame);
 
        int key = cv::waitKey(1);
 
        if (key == 'm') {
            showMask = !showMask;
        }
 
        if (showMask) {
            cv::imshow("Orange Mask", mask);
        } else {
            cv::destroyWindow("Orange Mask");
 
        }
 
        if (key == 'q') {
            break;
        }
    }
 
    return 0;
}
 