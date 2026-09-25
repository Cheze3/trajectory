#pragma once

#include <opencv2/core.hpp>
#include <chrono>
#include <cstddef>
#include <deque>


struct TimedPoint {
    cv::Point2f position;
    double timestamp;
};


class BallTracker {
public:
    explicit BallTracker(std::size_t maxHistory = 18);

    void addPosition(const cv::Point& position);

    void reset();

    const std::deque<TimedPoint>& getHistory() const;

    bool hasEnoughHistory(std::size_t minPoints = 5) const;

private:
    std::size_t maxHistory;
    std::deque<TimedPoint> history;
    std::chrono::steady_clock::time_point startTime;
    bool started = false;
};