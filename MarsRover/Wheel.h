//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_WHEEL_H
#define MARSROVER_WHEEL_H


#include "SceneObject.h"
#include "cmath"

class Wheel : public SceneObject {
public:
    /*
     * Radius of the wheel
     */
    GLdouble r;

    /*
     * Width of the wheel
     */
    GLdouble width;

    Wheel(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble r, GLdouble width);

    void draw() override;
};


#endif //MARSROVER_WHEEL_H
