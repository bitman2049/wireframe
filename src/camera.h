#pragma once
#include <eigen3/Eigen/Dense>
#include "color.h"

class Poly;
class Display;
class Point2d;

typedef Eigen::Matrix<double, 3, 4> CamMatrix;
typedef Eigen::Matrix4d ViewMatrix;

class Camera
{
public:
    Camera(Display* display);
    ~Camera();
    void lookAt(const Eigen::Vector4d& target, const double roll=0.0);
    const ViewMatrix& getViewMatrix() const {return mViewMatrix;}
    void setCamMatrix(CamMatrix m);
    const Eigen::Vector3d getPosition() const;
    void setPosition(const Eigen::Vector4d& p);
    Point2d project(const Eigen::Vector4d& p, const double focal);
    void rasterize(const Poly& poly, Color lineColor=Color(0xFFFFFFFF), Color fillColor=Color(0x00000000));
private:
    Display *mDisplay;
    Eigen::Vector4d mPosition;
    ViewMatrix mViewMatrix;
    double mFocalLen;
};
