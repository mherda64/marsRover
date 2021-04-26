//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_SCENEOBJECT_H
#define MARSROVER_SCENEOBJECT_H

#include <GL/freeglut.h>
#include "../BasicStructures/Point.h"
#include "../BasicStructures/Rotation.h"
#include <cmath>


class SceneObject {
public:
    Point position;
    Rotation rotation;
    const double PI = 3.14;

    SceneObject(const Point &position, const Rotation &rotation);

    SceneObject(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot);

    virtual void draw() = 0;

};


#endif //MARSROVER_SCENEOBJECT_H
