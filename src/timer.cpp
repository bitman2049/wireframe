#include "timer.h"
#include <chrono>
using namespace std::chrono_literals;

Timer::Timer() :
    mCurr(0ns),
    mStart(std::chrono::system_clock::now()),
    mIsRunning(false)
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    mIsRunning = true;
    mStart = std::chrono::system_clock::now();
    mCurr = 0ns;
}

void Timer::stop()
{
    update();
    mIsRunning = false;
}

void Timer::update()
{
    if (mIsRunning)
    {
        mCurr = std::chrono::system_clock::now() - mStart;
    }
}
