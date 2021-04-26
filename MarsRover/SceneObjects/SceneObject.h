//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_SCENEOBJECT_H
#define MARSROVER_SCENEOBJECT_H

#include <GL/freeglut.h>
#include "../BasicStructures/Point.h"
#include "../BasicStructures/Rotation.h"


class SceneObject {
public:
    Point position;
    Rotation rotation;

    SceneObject(const Point &position, const Rotation &rotation);

    SceneObject(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot);

    virtual void draw() = 0;

};


#endif //MARSROVER_SCENEOBJECT_H
