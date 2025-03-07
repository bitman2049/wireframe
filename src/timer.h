#pragma once
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void stop();
    void update();
    std::chrono::nanoseconds getCurr() const {return mCurr;}
private:
    std::chrono::nanoseconds mCurr;
    std::chrono::system_clock::time_point mStart;
    bool mIsRunning;
};
