//
// Created by musiek on 26.04.2021.
//

#ifndef MARSROVER_ROTATION_H
#define MARSROVER_ROTATION_H


#include <GL/freeglut.h>

/**
 * Structure like class representing a single rotation in 3d space
 */
class Rotation {
public:
    /**
     * Rotation in x axis
     */
    GLdouble xRot;

    /**
     * Rotation in y axis
     */
    GLdouble yRot;

    /**
     * Rotation in z axis
     */
    GLdouble zRot;

    Rotation(GLdouble xRot, GLdouble yRot, GLdouble zRot);
};


#endif //MARSROVER_ROTATION_H
