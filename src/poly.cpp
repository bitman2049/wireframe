#include "poly.h"
#include <iostream>

Face::Face(std::vector<int> vertices, Poly* parent, Color color) : 
    mVertices(vertices), 
    mColor(color),
    mParent(parent)
{ 
    const Eigen::Vector3d l1 = (getVertex(1) - getVertex(0)).block(0, 0, 3, 1);
    const Eigen::Vector3d l2 = (getVertex((mVertices.size() - 1)%mVertices.size()) - getVertex(0)).block(0, 0, 3, 1);
    const Eigen::Vector3d x = l2.cross(l1).normalized();
    mNormal = Eigen::Vector4d({x[0], x[1], x[2], 1});
}

void Face::getVertices(PointList& points)
{
    points.clear();
    points.reserve(mVertices.size());
    for (auto i : mVertices)
    {
        points.push_back(mParent->mPoints[i]);
    }
}

const Eigen::Vector4d Face::getVertex(const int i) const
{ 
    return mParent->mPoints[mVertices[i]];
}

Poly::Poly() : 
    mHomogeneous(Eigen::Matrix4d::Identity()),
    mRotation(Eigen::Matrix4d::Identity()),
    mId(0)
{
}

Poly::Poly(const PointList& points, const std::vector<std::vector<int>>& faces, const int id) :
    mPoints(points.cbegin(), points.cend()),
    mHomogeneous(Eigen::Matrix4d::Identity()),
    mRotation(Eigen::Matrix4d::Identity()),
    mId(id)
{
    for (auto f : faces)
    {
        mFaces.emplace_back(f, this);
    }
}

Poly::~Poly()
{
}

const Eigen::Vector4d Poly::getPosition() const
{
    return mHomogeneous.block(0, 3, 4, 1);
}

void Poly::getPoints(PointList& points) const
{
    for (const auto& p : mPoints)
    {
        points.push_back(mHomogeneous * p);
    }
}

void Poly::setRotation(const Eigen::Matrix4d& rotation)
{
    mRotation = rotation;
    mHomogeneous.block(0, 0, 3, 3) = rotation.block<3, 3>(0, 0);
}

const Eigen::Matrix4d& Poly::getRotation() const
{
    return mRotation;
}

void Poly::setPosition(const Eigen::Vector4d& position)
{
    mHomogeneous.block(0, 3, 4, 1) = position;
}

void Poly::setScale(const Eigen::Vector3d& scale)
{
    const Eigen::Matrix4d scaleMatrix = Eigen::Matrix4d({{scale[0], 0, 0, 0}, {0, scale[1], 0, 0}, {0, 0, scale[2], 0}, {0, 0, 0, 1}});
    for (auto& p : mPoints)
    {
        p = scaleMatrix * p;
    }
    mScale = scale;
}

void Poly::setScale(const double scale)
{
    return setScale(Eigen::Vector3d({scale, scale, scale}));
}

const Eigen::Vector4d Poly::getNormal(int faceIndex) const
{
    return mFaces[faceIndex].getNormal();
}
