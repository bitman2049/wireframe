#include "geometry.h"
#include <cmath>

const Eigen::Matrix4d Geometry::getRotMatrix(
        const double theta, const Eigen::Vector3d& axis, const bool normalize)
{
    const double scale = normalize?1.0/axis.norm():1.0;
    const double sint = std::sin(theta) * scale;
    const double q[] = {std::cos(theta), sint*axis(0), sint*axis(1), sint*axis(2)};
    const double q00 = q[0] * q[0];
    const double q01 = q[0] * q[1];
    const double q11 = q[1] * q[1];
    const double q02 = q[0] * q[2];
    const double q12 = q[1] * q[2];
    const double q22 = q[2] * q[2];
    const double q03 = q[0] * q[3];
    const double q13 = q[1] * q[3];
    const double q23 = q[2] * q[3];
    const double q33 = q[3] * q[3];
    return Eigen::Matrix4d(
        {
            {2*(q00 + q11) - 1, 2*(q12 - q03), 2*(q13 + q02), 0},
            {2*(q12 + q03), 2*(q00 + q22) - 1, 2*(q23 - q01), 0},
            {2*(q13 - q02), 2*(q23 + q01), 2*(q00 + q33) - 1, 0},
            {0, 0, 0, 1}
        }
    );

}

const Eigen::Matrix4d Geometry::getRotMatrix(
        const double theta, const Eigen::Vector4d& axis, const bool normalize)
{
    return getRotMatrix(theta, Eigen::Vector3d({axis[0], axis[1], axis[2]}), normalize);
}

const Eigen::Matrix4d Geometry::getPointAtMatrix(
        const Eigen::Vector4d& forward, const Eigen::Vector4d& up)
{
    const Eigen::Vector3d f = forward.block<3, 1>(0, 0).normalized();
    const Eigen::Vector3d r = f.cross(static_cast<Eigen::Vector3d>(up.block<3, 1>(0, 0))).normalized();
    const Eigen::Vector3d u = f.cross(r);
    return Eigen::Matrix4d({
            {r[0], r[1], r[2], 0.},
            {u[0], u[1], u[2], 0.},
            {f[0], f[1], f[2], 0.},
            {0., 0., 0., 1.}});
            
}

Eigen::Vector3d Geometry::project2d(const Eigen::Vector4d& p, const Eigen::Matrix4d& viewMatrix, const double focal)
{
    const Eigen::Vector4d viewp = viewMatrix * p;
    const double zscale = focal/viewp[2];
    return Eigen::Vector3d({viewp[0]*zscale, viewp[1]*zscale, viewp[2]}); 
}

void Geometry::makeLine(const Point2d &p0, const Point2d &p1, std::vector<Point2d> &outPoints)
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

void Geometry::makeShape(const std::vector<Point2d> &pts, std::vector<Point2d> &outPoints)
{
    const auto len = pts.size();
    for (int i = 0; i < len; i++)
    {
        std::vector<Point2d> line;
        makeLine(pts[i], pts[(i+1)%len], line);
        outPoints.insert(outPoints.end(), line.begin(), line.end());
    }
}

void Geometry::drawLine(const Point2d& p0, const Point2d& p1, Buffer<Color>& buffer)
{
    std::vector<Point2d> line;
    makeLine(p0, p1, line);
    for (auto p : line)
    {
        if (buffer.inbound(p))
            buffer(p) = 7;
    }
}
/*
void Geometry::drawFace(const Face& face, Buffer<ZObject> buffer)
{

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
*/
