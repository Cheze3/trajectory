#include <iostream>
#include <cmath>
#include <vector>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

constexpr double GRAVITY = 9.81;
constexpr double GROUND_Y = 450.0;
constexpr double PIXELS_PER_METER = 5.0;

void drawTrajectory(
    cv::Mat& image,
    const std::vector<cv::Point>& trajectory
) {
    cv::polylines(
        image,
        trajectory,
        false,
        cv::Scalar(0, 0, 255),
        2
    );
}

void calculateTrajectory(
    std::vector<cv::Point>& trajectory,
    double initialVelocity,
    double angle,
    double timeStep
) {
    double radianAngle = angle * CV_PI / 180.0;

    double flightTime =
        2.0 * initialVelocity * std::sin(radianAngle) / GRAVITY;

    for (double t = 0; t <= flightTime; t += timeStep) {

        double x =
            initialVelocity *
            std::cos(radianAngle) *
            t;

        double y =
            initialVelocity *
            std::sin(radianAngle) *
            t
            - 0.5 * GRAVITY * t * t;

        int pixelX =
            static_cast<int>(x * PIXELS_PER_METER);

        int pixelY =
            static_cast<int>(
                GROUND_Y - y * PIXELS_PER_METER
            );

        trajectory.push_back(
            cv::Point(pixelX, pixelY)
        );
    }
}

int main() {

    cv::Mat image(
        500,
        500,
        CV_8UC3,
        cv::Scalar(255, 255, 255)
    );

    std::vector<cv::Point> trajectory;

    double initialVelocity;
    double angle;
    double timeStep;

    std::cout << "Enter initial velocity (m/s): ";
    std::cin >> initialVelocity;

    std::cout << "Enter launch angle (degrees): ";
    std::cin >> angle;

    std::cout << "Enter time step (s): ";
    std::cin >> timeStep;

    if (initialVelocity <= 0) {
        std::cerr << "Velocity must be positive.\n";
        return 1;
    }

    if (angle < 0 || angle > 90) {
        std::cerr << "Angle must be between 0 and 90 degrees.\n";
        return 1;
    }

    if (timeStep <= 0) {
        std::cerr << "Time step must be positive.\n";
        return 1;
    }

    calculateTrajectory(
        trajectory,
        initialVelocity,
        angle,
        timeStep
    );

    drawTrajectory(image, trajectory);

    cv::imshow("Trajectory", image);
    cv::waitKey(0);

    return 0;
}