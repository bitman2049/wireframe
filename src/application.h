#pragma once
#include <memory>

class Timer;
class Scene;

class Application
{
public:
    Application();
    ~Application();
    void run();
    void update();
    void draw();
private:
    std::unique_ptr<Timer> mTimer;
    std::unique_ptr<Scene> mScene;
    bool mExit = false;
    int mFrames = 0;

};
