#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

bool detectBall(
    const cv::Mat& frame,
    cv::Point& ballPosition,
    cv::Mat& mask
);