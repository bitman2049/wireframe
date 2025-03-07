#pragma once
#include <eigen3/Eigen/Dense>

class Face;

class Point2d
{
public:
    Point2d(int x_, int y_) : x(x_), y(y_) {}
    Point2d(Eigen::Vector4d& v) : x(v[0]), y(v[1]) {}
    int x;
    int y;
    Point2d operator+(const Point2d& rhs) {return Point2d(x + rhs.x, y + rhs.y);}
    Point2d operator-(const Point2d& rhs) {return Point2d(x - rhs.x, y - rhs.y);}
};
Point2d operator+(const Point2d& lhs, const Point2d& rhs);
Point2d operator-(const Point2d& lhs, const Point2d& rhs);

struct ZObject
{
    // Default construct if an int is passed in. Done for compatibility with the Buffer class below
    ZObject(int) : z(1.0e20), face(nullptr) {} 
    ZObject(double z=1.0e20, Face* face=nullptr) : z(z), face(face) {}
    double z = 1.0e20;
    Face* face = nullptr;
    void reset() { z=1.0e20; face=nullptr; }
};

template<typename T>
class Buffer
{
public:
    Buffer() = default;
    Buffer(int wid, int hi) : mWid(wid), mHi(hi){mBuffer = std::vector<T>(wid*hi, static_cast<T>(0));}
    T& operator()(int x, int y){return mBuffer[y * mWid + x];}
    const T& operator()(int x, int y) const {return mBuffer[y * mWid + x];}
    T& operator()(Point2d p){return operator()(p.x, p.y);}
    const T& operator()(Point2d p) const {return operator()(p.x, p.y);}
    T& get(int x, int y){return operator()(x, y);}
    const T& get(int x, int y) const {return operator()(x, y);}
    int wid() const {return mWid;}
    int hi() const {return mHi;}
    void clr(){std::fill(mBuffer.begin(), mBuffer.end(), static_cast<T>(0));}
    bool inbound(int x, int y){return x >= 0 && x < mWid && y >= 0 && y < mHi;}
    bool inbound(Point2d p){return inbound(p.x, p.y);}
    const std::vector<T>& data() const { return mBuffer; }

private:
    int mWid = 8;
    int mHi = 8;
    std::vector<T> mBuffer = std::vector<T>(64, 0);
};

