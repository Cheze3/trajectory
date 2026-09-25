#pragma once

#include <opencv2/core.hpp>
#include <deque>
#include <vector>

#include "tracker.hpp"

std::vector<cv::Point> predictTrajectory(
    const std::deque<TimedPoint>& history,
    double predictSeconds = 0.5,
    int numPredictedPoints = 15
);