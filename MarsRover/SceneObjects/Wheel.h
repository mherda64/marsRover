//
// Created by musiek on 4/16/21.
//

#ifndef MARSROVER_WHEEL_H
#define MARSROVER_WHEEL_H


#include "SceneObject.h"

/**
 * Class representing a wheel - cyllinder shape. Extends SceneObject class.
 */
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

    /*
     * Position of the wheel over the floor level. Used to create dynamic suspension of the rover
     */
    GLdouble valueOverFloor;

    Wheel(GLdouble x, GLdouble y, GLdouble z, GLdouble xRot, GLdouble yRot, GLdouble zRot, GLdouble r, GLdouble width, GLdouble valueOverFloor);

    /**
     * Constructor of the wheel class.
     * @param position Position of the wheel in 3d space.
     * @param rotation Rotation of the wheel in 3d space.
     * @param r Radius of the wheel.
     * @param width Width of the wheel.
     * @param valueOverFloor Current height/altitude over the floor level.
     */
    Wheel(const Point &position, const Rotation &rotation, GLdouble r, GLdouble width, GLdouble valueOverFloor);

    void draw() override;
};


#endif //MARSROVER_WHEEL_H
