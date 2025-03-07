#pragma once

#include <eigen3/Eigen/Dense>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include <cstdlib>
#include <string>
#include "camera.h"
#include <atomic>
#include <thread>
#include <condition_variable>
#include "color.h"
#include "buffer.h"

class Display
{
public:
    Display() = default;
    ~Display();
    void initialize();
    void update();
    void draw();
    static void makeLine(const Point2d &p0, const Point2d &p1, std::vector<Point2d> &outPoints);
    void drawLine(const Point2d &p0, const Point2d &p1);
    static void makeShape(const std::vector<Point2d> &pts, std::vector<Point2d> &outPoints);
    void drawShape(const Eigen::Vector4d norm, const std::vector<Point2d> &pts, Color lineColor=Color(0xFFFFFFFF), Color fillColor=Color(0x00000000), bool hideBack=true);
    static void toStrings(const Buffer<Color>& buffer, std::vector<std::wstring>& output);
    static void toColorMap(const Buffer<Color>& buffer, Buffer<int>& colorMap);
    void drawThread();
    static short getColorIndex(const short c){return ((c+9)&0xf) | (c&0xf0);}

    std::shared_ptr<Camera> mCamera;
private:
    bool mColor = true;
    std::mutex mBuffLock;
    std::atomic_bool mWait;
    std::condition_variable mDrawVar;
    std::mutex mDrawLock;
    std::atomic_bool mExit;
    std::unique_ptr<Buffer<Color>> mFrontBuffer;
    std::unique_ptr<Buffer<Color>> mBackBuffer;
    std::shared_ptr<std::thread> mDrawThread;
    std::unique_ptr<Buffer<ZObject>> mZBuff;
};
