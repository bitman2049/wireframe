#include "camera.h"
#include <cmath>
#include "geometry.h"
#include "poly.h"
#include "display.h"
#include <ncurses.h>

Camera::Camera(Display* display) : mPosition(Eigen::Vector4d({0, 0, 0, 0})), mViewMatrix(Eigen::Matrix4d::Identity()), mDisplay(display)
{
}

Camera::~Camera()
{
}

void Camera::lookAt(const Eigen::Vector4d& target, const double roll)
{
    const Eigen::Vector3d f = (target - mPosition).block<3, 1>(0, 0).normalized();
    const Eigen::Matrix3d rot = roll==0.0?Eigen::Matrix3d::Identity():static_cast<Eigen::Matrix3d>(Geometry::getRotMatrix(roll, f, false).block<3, 3>(0, 0));
    const Eigen::Vector3d r = f.cross(rot * Eigen::Vector3d({0, 1, 0})).normalized();
    const Eigen::Vector3d u = r.cross(f);
    const Eigen::Vector3d position3d = mPosition.block<3, 1>(0, 0);
    mViewMatrix <<
        r[0], r[1], r[2], -position3d.dot(r),
        u[0], u[1], u[2], -position3d.dot(u),
        f[0], f[1], f[2], -position3d.dot(f),
        0, 0, 0, 1;
}

void Camera::setPosition(const Eigen::Vector4d& p)
{
    mPosition = p;
}

Point2d Camera::project(const Eigen::Vector4d& p, const double focal)
{
    const Eigen::Vector4d viewp = getViewMatrix() * p;
    const double zscale = -focal/viewp[2];
    return Point2d(viewp[0]*zscale + COLS/2, viewp[1]*zscale + LINES); 

}

void Camera::rasterize(const Poly& poly, Color lineColor, Color fillColor)
{
    std::vector<Point2d> rasterPoints;
    PointList points;
    poly.getPoints(points);
    for (auto p : points)
    {
        rasterPoints.push_back(project(p, 100));
    }
    std::vector<std::vector<Point2d>> rasterFaces;
    int fin = 0;
    for (const auto& f : poly.getFaces())
    {
        std::vector<Point2d> face;
        for (const auto i : f.getVertexIndices())
        {
            face.push_back(rasterPoints[i]);
        }
        //int n = poly.getNormal(fin).dot(Eigen::Vector3d({0, 1. 0}));
        mDisplay->drawShape(poly.getRotation() * f.getNormal(), face, lineColor, f.getColor());
        fin++;
    }
}
