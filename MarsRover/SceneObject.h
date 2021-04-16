//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_SCENEOBJECT_H
#define MARSROVER_SCENEOBJECT_H

#include <GL/glut.h>


class SceneObject {
public:
    GLdouble x;
    GLdouble y;
    GLdouble z;
    GLdouble xRot;
    GLdouble yRot;
    GLdouble zRot;

    SceneObject(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot);

    virtual void draw() = 0;

};


#endif //MARSROVER_SCENEOBJECT_H
