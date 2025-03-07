#pragma once
#include <vector>
#include <eigen3/Eigen/Dense>
#include "color.h"

typedef std::vector<Eigen::Vector4d> PointList;

class Poly;

class Face
{
public:
    Face(std::vector<int> vertices, Poly* parent, Color color=Color(0xFF888888)); 
    ~Face() {mParent = nullptr;}
    const std::vector<int> getVertexIndices() const { return mVertices; }
    void getVertices(PointList& points);
    const Eigen::Vector4d getVertex(const int i) const;
    const Eigen::Vector4d& getNormal() const { return mNormal; }
    const Color& getColor() const { return mColor; }
    void setColor(const Color& color) { mColor = color; }
private:
    Eigen::Vector4d mNormal;
    std::vector<int> mVertices;
    Color mColor;
    Poly* mParent;
};

typedef std::vector<Face> FaceList;

class Poly
{
public:
    Poly();
    Poly(const PointList& points, const std::vector<std::vector<int>>& faces, const int id=0);
    Poly(const Poly& other, int id=-1) : mPoints(other.mPoints), mFaces(other.mFaces), mId(other.mId), mHomogeneous(other.mHomogeneous), mScale(other.mScale) {if (id != -1) mId = id; }
    ~Poly();
    void draw();
    const PointList& getBasePoints() const {return mPoints;}
    void getPoints(PointList& points) const;
    const FaceList& getFaces() const {return mFaces;}
    FaceList& getFaces() { return mFaces; }
    void setPosition(const Eigen::Vector4d& position);
    const Eigen::Vector4d getPosition() const;
    void setRotation(const Eigen::Matrix4d& rotation);
    const Eigen::Matrix4d& getRotation() const;
    void setPosAndRot(const Eigen::Vector4d& position, const Eigen::Matrix4d rotation);
    const Eigen::Matrix4d& getHomogeneous() const { return mHomogeneous; }
    void setScale(const Eigen::Vector3d& scale);
    void setScale(const double scale);
    const Eigen::Vector3d& getScale() const {return mScale;}
    const Eigen::Vector4d getNormal(int faceIndex) const;
    int id() const { return mId; }
private:
    PointList mPoints;
    FaceList mFaces;
    Eigen::Matrix4d mHomogeneous;
    Eigen::Matrix4d mRotation;
    Eigen::Vector3d mScale;
    int mId;
    friend class Face;
};
