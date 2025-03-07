#pragma once
#include <eigen3/Eigen/Dense>
#include "buffer.h"
#include "color.h"

class Geometry
{
    
public:
    static const Eigen::Matrix4d getRotMatrix(
            const double theta, const Eigen::Vector3d& axis, const bool normalize=true);
    static const Eigen::Matrix4d getRotMatrix(
            const double theta, const Eigen::Vector4d& axis, const bool normalize=true);
    static const Eigen::Matrix4d getPointAtMatrix(
            const Eigen::Vector4d& forward, const Eigen::Vector4d& up=Eigen::Vector4d({0, 1, 0, 0}));
    static void makeLine(const Point2d &p0, const Point2d &p1, std::vector<Point2d> &outPoints);
    static void makeShape(const std::vector<Point2d> &pts, std::vector<Point2d> &outPoints);
    static void drawLine(const Point2d& p0, const Point2d& p1, Buffer<Color>& buffer);
    static void drawFace(const Face& face, Buffer<Color>& buffer);
    static Eigen::Vector3d project2d(
            const Eigen::Vector4d& p, const Eigen::Matrix4d& viewMatrix, const double focal);
};
