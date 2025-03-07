#include "display.h"
#include "timer.h"
#include <cmath>
#include <thread>
#include <condition_variable>
#include "color.h"
#include <ncurses.h>
#include "poly.h"

static const wchar_t* blocks_w = L" ▀▄█";
const std::chrono::nanoseconds cFrameDur = std::chrono::nanoseconds(1000000000/60);

void Display::toStrings(const Buffer<Color>& buffer, std::vector<std::wstring>& output)
{
    Buffer<int> indices = Buffer<int>(buffer.wid(), (buffer.hi()+1)/2);
    for (int y = 0; y < buffer.hi(); y++)
    {
        for (int x = 0; x < buffer.wid(); x++)
        {
            int inc = 1;
            if (y % 2 != 0)
                inc = 2;
            if (buffer(x, y).a && (buffer(x, y).r || buffer(x, y).g || buffer(x, y).b))
            {
                indices(x, y/2) += inc;
            }
        }
    }
    output.clear();
    for (int y = 0; y < indices.hi(); y++)
    {
        std::vector<wchar_t> wchars(indices.wid());
        for (int x = 0; x < indices.wid(); x++)
        {
            wchars[x] = blocks_w[indices(x, y)];
        }
        output.emplace_back(wchars.begin(), wchars.end());
    }

}

void Display::toColorMap(const Buffer<Color>& buffer, Buffer<int>& colorMap)
{
    colorMap = Buffer<int>(buffer.wid(), (buffer.hi()+1)/2);
    for (int y = 0; y < buffer.hi(); y++)
    {
        for (int x = 0; x < buffer.wid(); x++)
        {
            colorMap(x, y>>1) |= ((buffer(x, y).dither(x, y)&15) << ((y&1) << 2));
            //colorMap(x, y>>1) |= ((buffer(x, y).quantize()&15) << ((y&1) << 2));
        }
    }
}

void Display::initialize()
{
    initscr();
    mFrontBuffer = std::make_unique<Buffer<Color>>(COLS, LINES * 2 - 2);
    mBackBuffer = std::make_unique<Buffer<Color>>(COLS, LINES * 2 - 2);
    mZBuff = std::make_unique<Buffer<ZObject>>(COLS, LINES * 2 - 2);
    cbreak();
    noecho();
    curs_set(0);
    start_color();
    move(0, 0);
    for (short i = 0; i < 256; i++)
    {
        init_pair(i, (i+7)%16, i/16);
    }
    nodelay(stdscr, true);
    keypad(stdscr, TRUE);
    setlocale(LC_ALL, "");
    clear();
    mCamera = std::make_unique<Camera>(this);
    mExit = false;
    mWait = true;
    mDrawThread = std::make_shared<std::thread>(&Display::drawThread, this);
}

Display::~Display()
{
    mExit = true;
    update();
    mDrawThread->join();
    endwin();
}

void Display::update()
{
    //mZBuff->clr();
    mWait = false;
    mDrawVar.notify_all();
}

void Display::drawThread()
{
    while (!mExit)
    {
        std::unique_lock<std::mutex> lock(mDrawLock);
        mDrawVar.wait(lock, [this]{return this->mWait==false;});
        mWait = true;
        draw();
    }
}

void Display::draw()
{   
    mBuffLock.lock();
    mFrontBuffer.swap(mBackBuffer);
    mBuffLock.unlock();
    if (!mColor)
    {
        std::vector<std::wstring> strings;
        toStrings(*mFrontBuffer, strings);
        move(0, 0);
        for (const auto& s : strings)
        {
            addwstr(s.data());
        }
    }
    else
    {
        Buffer<int> colorMap;
        toColorMap(*mFrontBuffer, colorMap);
        move(0, 0);
        int i = 0;
        for (const auto c : colorMap.data())
        {
            cchar_t blk;
            const short index = getColorIndex(c);
            setcchar(&blk, L"▀", COLOR_PAIR(index), index, NULL); 
            add_wch(&blk);
        }
    }
    refresh();
    mFrontBuffer->clr();
}

void Display::makeLine(const Point2d &p0, const Point2d &p1, std::vector<Point2d> &outPoints)
{
    const int dx = p1.x - p0.x;
    const int dy = p1.y - p0.y;
    if (dx == 0)
    {
        for (int y = std::min(p0.y, p1.y); y <= std::max(p0.y, p1.y); ++y)
        {
            outPoints.emplace_back(p0.x, y);
        }
    }
    else if (dy == 0)
    {
        for (int x = std::min(p0.x, p1.x); x <= std::max(p0.x, p1.x); ++x)
        {
            outPoints.emplace_back(x, p0.y);
        }
    }
    else
    {
        const int adx = abs(dx);
        const int ady = -abs(dy);
        const int sx = adx/dx;
        const int sy = -ady/dy;
        int error = adx + ady;
        int x = p0.x;
        int y = p0.y;
        while (x != p1.x or y != p1.y)
        {
            outPoints.emplace_back(x, y);
            int e2 = 2*error;
            if (e2 >= ady)
            {
                if (x == p1.x)
                {
                    break;
                }
                error += ady;
                x += sx;
            }
            if (e2 <= adx)
            {
                if (y == p1.y)
                {
                    break;
                }
                error += adx;
                y += sy;
            }
        }
    }
}

void Display::makeShape(const std::vector<Point2d> &pts, std::vector<Point2d> &outPoints)
{
    const auto len = pts.size();
    for (int i = 0; i < len; i++)
    {
        std::vector<Point2d> line;
        makeLine(pts[i], pts[(i+1)%len], line);
        outPoints.insert(outPoints.end(), line.begin(), line.end());
    }
}

void Display::drawLine(const Point2d& p0, const Point2d& p1)
{
    std::vector<Point2d> line;
    makeLine(p0, p1, line);
    mBuffLock.lock();
    for (auto p : line)
    {
        if (mBackBuffer->inbound(p))
            (*mBackBuffer)(p) = 7;
    }
    mBuffLock.unlock();
}

void Display::drawShape(const Eigen::Vector4d norm, const std::vector<Point2d> &pts, Color lineColor, Color fillColor, bool hideBack)
{
    float scale = fillColor.a?norm.dot(Eigen::Vector4d({1, 1, -1, 0}).normalized()):1.0;
    fillColor.a = true;
    if (pts.size() < 3)
    {
        drawLine(pts[0], pts[1]);
        return;
    }
    if (hideBack)
    {
        Point2d l1 = pts[1] - pts[0];
        Point2d l2 = pts[(pts.size()-1)%pts.size()] - pts[0];
        if (l1.x * l2.y - l2.x * l1.y >= 0)
        {
            return;
        }
    }
    mBuffLock.lock();
    std::vector<Point2d> shape;
    makeShape(pts, shape);
    int minx = mBackBuffer->wid();
    int maxx = -1;
    int miny = mBackBuffer->hi();
    int maxy = -1;
    if (fillColor.a)
    {
        for (auto p : shape)
        {
            if (mBackBuffer->inbound(p))
            {
                minx = std::min(p.x, minx);
                maxx = std::max(p.x, maxx);
                miny = std::min(p.y, miny);
                maxy = std::max(p.y, maxy);
            }
        }
        for (int y = miny; y <= maxy; y++)
        {
            for (int x = minx; x <= maxx; x++)
            {
                Point2d p = Point2d(x, y);
                bool isvisible = true;
                for (int i = 0; i < pts.size(); i++)
                {
                    Point2d l1 = pts[(i+1)%pts.size()] - pts[i];
                    Point2d l2 = p - pts[i];
                    if (l1.x * l2.y - l2.x * l1.y > 0)
                    {
                        isvisible = false;
                        break;
                    }
                }
                if (isvisible)
                    (*mBackBuffer)(p) = fillColor * scale;
            }
        }
    }
    if (lineColor.a)
    {
        for (auto p : shape)
        {
            if (mBackBuffer->inbound(p) && scale < 0)
            {
                (*mBackBuffer)(p) = fillColor*(scale!=1.0?-scale:1.0);
            }
        }
    }
    mBuffLock.unlock();
}
