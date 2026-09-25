#include "tracker.hpp"

BallTracker::BallTracker(std::size_t maxHistory)
    : maxHistory(maxHistory) {
}

void BallTracker::addPosition(const cv::Point& position) {

    auto now = std::chrono::steady_clock::now();

    if (!started) {
        startTime = now;
        started = true;
    }

    double elapsedSeconds = std::chrono::duration<double>(
        now - startTime
    ).count();

    history.push_back(TimedPoint{
        cv::Point2f(
            static_cast<float>(position.x),
            static_cast<float>(position.y)
        ),
        elapsedSeconds
    });

    while (history.size() > maxHistory) {
        history.pop_front();
    }
}

void BallTracker::reset() {
    history.clear();
    started = false;
}

const std::deque<TimedPoint>& BallTracker::getHistory() const {
    return history;
}

bool BallTracker::hasEnoughHistory(std::size_t minPoints) const {
    return history.size() >= minPoints;
}