#pragma once
#include <vector>
#include <memory>

class Poly;
class Camera;
class Display;

class Scene
{
public:
    Scene();
    ~Scene();
    void update();
    void draw();
    void setDisplay(std::shared_ptr<Display> display);
    int addPolygon(std::shared_ptr<Poly> p);
    int mFrames;
    int zsort(std::shared_ptr<Poly> p1, std::shared_ptr<Poly> p2);
private:
    std::vector<std::shared_ptr<Poly>> mPolygons;
    std::shared_ptr<Camera> mCamera;
    std::shared_ptr<Display> mDisplay;

};
