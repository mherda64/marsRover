#pragma once
#include "SceneObject.h"
class Afterburner :
    public SceneObject
{
public:
    GLdouble topRadius; /* radius of top of the afterburner*/
    GLdouble bottomRadius; /* radius of bottom of the afterburner*/
    GLdouble height; /* height of afterburner*/
    GLdouble innerRadius; /* radius of bottom inside the afterburner*/


    Afterburner(const Point& position, const Rotation& rotation, GLdouble topRadius, GLdouble bottomRadius, GLdouble height, GLdouble innerRadius);


    void draw() override;
};

