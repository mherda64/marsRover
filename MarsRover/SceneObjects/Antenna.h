#pragma once
#include "SceneObject.h"
class Antenna :
    public SceneObject
{
private:
    bool animationDirection = true;
public:

    GLdouble r;/**<Radius of the antena*/

    float speed; /**< Speed of antenna animation*/
    
    GLdouble width;/**< With of antenna base*/

    Antenna(const Point& position, const Rotation& rotation, GLdouble r, GLdouble width,float speed);

    void draw() override;
};

