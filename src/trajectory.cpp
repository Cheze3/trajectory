#include "trajectory.hpp"

#include <opencv2/core.hpp>

namespace {


bool fitLinear(
    const std::deque<TimedPoint>& history,
    double& a,
    double& b
) {
    int n = static_cast<int>(history.size());

    cv::Mat A(n, 2, CV_64F);
    cv::Mat B(n, 1, CV_64F);

    for (int i = 0; i < n; i++) {

        double t = history[i].timestamp;

        A.at<double>(i, 0) = t;
        A.at<double>(i, 1) = 1.0;

        B.at<double>(i, 0) = history[i].position.x;
    }

    cv::Mat X;

    if (!cv::solve(A, B, X, cv::DECOMP_SVD)) {
        return false;
    }

    a = X.at<double>(0, 0);
    b = X.at<double>(1, 0);

    return true;
}

bool fitQuadratic(
    const std::deque<TimedPoint>& history,
    double& a,
    double& b,
    double& c
) {
    int n = static_cast<int>(history.size());

    cv::Mat A(n, 3, CV_64F);
    cv::Mat B(n, 1, CV_64F);

    for (int i = 0; i < n; i++) {

        double t = history[i].timestamp;

        A.at<double>(i, 0) = t * t;
        A.at<double>(i, 1) = t;
        A.at<double>(i, 2) = 1.0;

        B.at<double>(i, 0) = history[i].position.y;
    }

    cv::Mat X;

    if (!cv::solve(A, B, X, cv::DECOMP_SVD)) {
        return false;
    }

    a = X.at<double>(0, 0);
    b = X.at<double>(1, 0);
    c = X.at<double>(2, 0);

    return true;
}

}

std::vector<cv::Point> predictTrajectory(
    const std::deque<TimedPoint>& history,
    double predictSeconds,
    int numPredictedPoints
) {
    std::vector<cv::Point> predicted;

    const std::size_t MIN_POINTS = 5;

    if (history.size() < MIN_POINTS || numPredictedPoints <= 0) {
        return predicted;
    }

    double firstTimestamp = history.front().timestamp;
    double lastTimestamp = history.back().timestamp;

    const double MIN_TIME_SPAN = 0.05;

    if (lastTimestamp - firstTimestamp < MIN_TIME_SPAN) {
        // Samples are too tightly clustered in time for a stable fit.
        return predicted;
    }

    double ax = 0.0;
    double bx = 0.0;

    double ay = 0.0;
    double by = 0.0;
    double cy = 0.0;

    if (!fitLinear(history, ax, bx)) {
        return predicted;
    }

    if (!fitQuadratic(history, ay, by, cy)) {
        return predicted;
    }

    predicted.reserve(numPredictedPoints);

    for (int i = 1; i <= numPredictedPoints; i++) {

        double t = lastTimestamp + (predictSeconds * i) / numPredictedPoints;

        double x = ax * t + bx;
        double y = ay * t * t + by * t + cy;

        predicted.emplace_back(
            static_cast<int>(x),
            static_cast<int>(y)
        );
    }

    return predicted;
}