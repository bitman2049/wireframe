#pragma once
#include <eigen3/Eigen/Dense>

class Sphere
{
public:
    Sphere(Eigen::Vector4d& position, double radius) : mPosition(position), mRadius(radius) {}
    void setPosition(const Eigen::Vector4d& position) {mPosition = position;}
    const Eigen::Vector4d& getPosition() const { return mPosition; }
    void setRadius(const double radius) { mRadius = radius; }
    double getRadius() const { return mRadius; }
private:
    Eigen::Vector4d mPosition;
    double mRadius;
}
