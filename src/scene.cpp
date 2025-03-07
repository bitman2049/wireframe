#include "scene.h"

#include "display.h"
#include "camera.h"
#include "poly.h"
#include "ships.h"
#include "geometry.h"
#include <algorithm>
#include <ncurses.h>
#include "color.h"

Scene::Scene()
{
    mFrames = 0;
    mDisplay = std::make_unique<Display>();
    std::shared_ptr<Poly> coriolis = std::make_shared<Poly>(Ship::Coriolis, 0);
    coriolis->setScale(2.0);
    coriolis->getFaces()[1].setColor(Color(0x00FFFFFF));
    std::shared_ptr<Poly> viper = std::make_shared<Poly>(Ship::CobraMk3, 1);
    viper->setScale(1.0);
    viper->getFaces()[10].setColor(Color(0x00FF0000));
    viper->getFaces()[11].setColor(Color(0x00FF0000));
    mPolygons.push_back(coriolis);
    mPolygons.push_back(viper);
    mDisplay->initialize();
    mDisplay->mCamera->setPosition(Eigen::Vector4d({550, 140, 750, 1}));
}

Scene::~Scene()
{
}

void Scene::setDisplay(std::shared_ptr<Display> display)
{
}

void Scene::update()
{
    double pcos = cos(mFrames/120.0);
    double psin = sin(mFrames/120.0);

    Eigen::Matrix4d matRot = Geometry::getRotMatrix(
            mFrames/350.0, Eigen::Vector3d({0, 1, 0}));
    Eigen::Matrix4d camRot = Geometry::getRotMatrix(
            mFrames/350.0, static_cast<Eigen::Vector4d>(matRot * Eigen::Vector4d({pcos, 30, 0, 1})));
    Eigen::Matrix4d coriolisRot = Geometry::getRotMatrix(
            mFrames/573.0, Eigen::Vector3d({0, 0, 1}));
    mPolygons[0]->setPosition(Eigen::Vector4d({0, 0, 0, 1}));
    mPolygons[0]->setRotation(coriolisRot);
    mPolygons[1]->setPosition(matRot*Eigen::Vector4d({-600, 0, 0, 1}));
    mPolygons[1]->setRotation(matRot*Geometry::getRotMatrix(mFrames/100., Eigen::Vector3d({0, 0, 1})));
    //mDisplay->mCamera->setPosition(camRot * Eigen::Vector4d({-1000, 0, 0, 1}));
    mDisplay->mCamera->lookAt(Eigen::Vector4d({0, 0, 0, 0}));

    mFrames += 1;
}

void Scene::draw()
{
    std::vector<std::shared_ptr<Poly>> temp(mPolygons);
    std::sort(temp.begin(), temp.end(), [this](std::shared_ptr<Poly> p1, std::shared_ptr<Poly> p2){
    return (this->mDisplay->mCamera->getViewMatrix() * p1->getPosition())[2] > (this->mDisplay->mCamera->getViewMatrix() * p2->getPosition())[2];});

    for (const auto poly : temp)
    {
        mDisplay->mCamera->rasterize(*poly, Color(0xFFFFFFFF), Color(0, 0, 255));
    }
    mDisplay->update();
}

int Scene::addPolygon(std::shared_ptr<Poly> p)
{
    mPolygons.push_back(p);
    return mPolygons.size() - 1;
}
