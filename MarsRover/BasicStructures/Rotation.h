//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_ROTATION_H
#define MARSROVER_ROTATION_H


#include <GL/freeglut.h>

class Rotation {
public:
    GLdouble xRot;
    GLdouble yRot;
    GLdouble zRot;

    Rotation(GLdouble xRot, GLdouble yRot, GLdouble zRot);
};


#endif //MARSROVER_ROTATION_H
