#include "detector.hpp"
#include <opencv2/imgproc.hpp>

bool detectBall(
    const cv::Mat& frame,
    cv::Point& ballPosition
) {
    
    cv::Mat hsv;
    cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

    cv::Scalar lowerOrange(8, 150, 120);
    cv::Scalar upperOrange(20, 255, 255);

    cv::Mat mask;
    cv::inRange(hsv, lowerOrange, upperOrange, mask);

    cv::Mat labels;
    cv::Mat stats;
    cv::Mat centroids;

    int numberOfObjects = cv::connectedComponentsWithStats(
        mask,
        labels,
        stats,
        centroids
    );

    if (numberOfObjects <= 1) {
        return false;
    }

    int largestObject = 1;

    for (int i = 2; i < numberOfObjects; i++) {

        int currentArea = stats.at<int>(
            i,
            cv::CC_STAT_AREA
        );

        int largestArea = stats.at<int>(
            largestObject,
            cv::CC_STAT_AREA
        );

        if (currentArea > largestArea) {
            largestObject = i;
        }
    }

    ballPosition.x = static_cast<int>(
        centroids.at<double>(largestObject, 0)
    );

    ballPosition.y = static_cast<int>(
        centroids.at<double>(largestObject, 1)
    );

    return true;
}