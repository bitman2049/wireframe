#include "application.h"
#include <ncurses.h>
#include <thread>
#include <chrono>
#include "timer.h"
#include "scene.h"

const std::chrono::nanoseconds cFrameDur = std::chrono::nanoseconds(1000000000/60);

Application::Application()
{
    mTimer = std::make_unique<Timer>();
    mScene = std::make_unique<Scene>();
}

Application::~Application()
{
}

void Application::run()
{
    while (!mExit)
    {
        mTimer->start();
        update();
        draw();
        if (getch() == 'q')
        {
            mExit = true;
        }
        mTimer->stop();
        if (mTimer->getCurr() < cFrameDur)
        {
            std::this_thread::sleep_for(cFrameDur - mTimer->getCurr());
        }
    }
}

void Application::update()
{
    mScene->update();
}

void Application::draw()
{
    mScene->draw();
}
